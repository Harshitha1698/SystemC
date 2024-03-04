#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <random>

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>


class processor : public sc_module, tlm::tlm_bw_transport_if<>
{

    


private:
	std::ifstream file;  //An input file stream used for reading the trace.
	sc_time cycleTime;  //Represents the cycle time.

	// Method:
    void processTrace();
    void processRandom();

	//quantum keeper
	tlm_utils::tlm_quantumkeeper quantumKeeper;

public:
	tlm::tlm_initiator_socket<> iSocket;  //An initiator socket for TLM communication.

	processor(sc_module_name, std::string pathToTrace, sc_time cycleTime);  //	Declaration of Constructor

	SC_HAS_PROCESS(processor);
	// This macro is used to indicate that the processor class contains a SystemC process. 
	// This is necessary when you want to use SC_THREAD or SC_METHOD macros within the class to define the behavior of the module.

	// Dummy method:
    void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64)
	{
		SC_REPORT_FATAL(this->name(), "invalidate_direct_mem_ptr not implement");
	}

	// Dummy method:
    tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &,tlm::tlm_phase &, sc_time &)
	{
		SC_REPORT_FATAL(this->name(), "nb_transport_bw is not implemented");
		return tlm::TLM_ACCEPTED;
	}
};

//Implementation of Constructor
processor::processor(sc_module_name, std::string pathToFile, sc_time cycleTime) :
	file(pathToFile), cycleTime(cycleTime)
{
	if (!file.is_open()) {
		std::cout << "Opening trace file at: " << pathToFile << std::endl;
		SC_REPORT_FATAL(name(), "Could not open trace");
	}
		
    //SC_THREAD(processTrace);
	SC_THREAD(processRandom); //this will not use trace file but internally generates random address and timestamps.

	iSocket.bind(*this);

	//Quantum Keeper
	quantumKeeper.set_global_quantum(sc_time(100000,SC_NS)); // STATIC!
    quantumKeeper.reset();
}

// Use the command below in a termial to get your gcc version.
// $ gcc --version
// If it is less than 4.9 uncomment the definition that follows.
//#define GCC_LESS_THAN_4_9_DOES_NOT_SUPPORT_REGEX

void processor::processTrace()
{
	wait(SC_ZERO_TIME);
	//This line uses the wait statement to suspend the execution of the processTrace method until time SC_ZERO_TIME.
	//Essentially, it's a way to introduce an initial delay before starting the processing.

    std::string line;  //string variable line
	tlm::tlm_generic_payload trans; //creating a payload trans
	uint64_t cycles = 0;
	uint64_t address = 0;
	std::string dataStr; // Declares a string variable dataStr
	unsigned char data[4]; //Declares an array data of type unsigned char and size 4.
	bool read = true; //read flag

    while (std::getline(file, line))
	{
#ifdef GCC_LESS_THAN_4_9_DOES_NOT_SUPPORT_REGEX
		// Available GCC is too old and it does not have support to regular
		// expressions (version <= 4.9).
		//If the compiler version doesn't support regular expressions, this block of code is used to manually parse the trace line.
		std::string time;
		std::string command;
		std::string addr;
		std::istringstream iss(line); //std::istringstream to extract timestamp, command, address, and data (if applicable) from the trace line.
		// Get the timestamp for the transaction.
		iss >> time;
		if (time.empty()) {
			SC_REPORT_FATAL(name(), "Syntax error in trace");
		}
		cycles = std::stoull(time.c_str(), nullptr, 10);

		// Get the command.
		iss >> command;
		if (command.empty()) {
			SC_REPORT_FATAL(name(), "Syntax error in trace");
		}
		if (command == "read") {
			read = true;
		} else if (command == "write") {
			read = false;
		} else {
			SC_REPORT_FATAL(name(), "Syntax error in trace");
		}

		// Get the address.
		iss >> addr;
		if (addr.empty()) {
			SC_REPORT_FATAL(name(), "Syntax error in trace");
		}
		address = std::stoull(addr.c_str(), nullptr, 16);

		// Get the data if transaction is a write.
		if (read == false) {
			iss >> dataStr;
			if (dataStr.empty()) {
				SC_REPORT_FATAL(name(), "Syntax error in trace");
			}
			unsigned long long d = std::stoull(dataStr.c_str(), nullptr, 16);  //std::stoull to convert the hexadecimal string to an integer.
			data[0] = (unsigned char)((d & 0xff000000) >> 24);
			data[1] = (unsigned char)((d & 0x00ff0000) >> 16);
			data[2] = (unsigned char)((d & 0x0000ff00) >> 8);
			data[3] = (unsigned char)((d & 0x000000ff) >> 0);

			// d & 0xff000000: Retrieves the most significant byte.>> 24: Shifts the byte to the least significant position.
			// (unsigned char): Casts the result to an unsigned char.
			//this block of code extracts the hexadecimal data value from the trace line, converts it to an unsigned long long integer, and then breaks it down into four bytes, storing them in the data array. 
		}

#else
		// Available GCC has support to regular expressions (version >= 4.9)
		std::regex reW("(\\d+)\\s*:\\s*write\\s+0x([\\d\\w]+)\\s+0x([\\d\\w]+)");
		// 	\\d+: Matches one or more digits (the cycle count).
		// \\s*: Matches zero or more whitespace characters.
		// write: Matches the literal string "write".
		// 0x([\\d\\w]+): Capturing group for the first hexadecimal number (memory address).
		// \\s+: Matches one or more whitespace characters.
		// 0x([\\d\\w]+): Capturing group for the second hexadecimal number (data value).
		std::regex reR("(\\d+)\\s*:\\s*read\\s+0x([\\d\\w]+)");

		// \\d+: Matches one or more digits (the cycle count).
		// \\s*: Matches zero or more whitespace characters.
		// read: Matches the literal string "read".
		// \\s+: Matches one or more whitespace characters.
		// 0x([\\d\\w]+): Capturing group for the hexadecimal number (memory address).
		// In both regular expressions:
		// \\d represents a digit.
		// \\w represents a word character (alphanumeric or underscore).
		// \\s represents a whitespace character.

		std::smatch matchW;
		std::smatch matchR;   //std::smatch class is part of the <regex> library and is used to store the results of a regular expression match.

		if (std::regex_search(line, matchW, reW) && matchW.size() > 1)  //reW is write operation
		{
			cycles = std::stoull(matchW.str(1), nullptr, 10);
			read = false;
			address = std::stoull(matchW.str(2), nullptr, 16);
			dataStr = matchW.str(3);
			for(int i = 0; i < 4; i++)
			{
				data[i] = (unsigned char) std::stoi(dataStr.substr(i * 2, 2), //It effectively extracts pairs of hexadecimal characters from the string.
						nullptr,
						16);
			}
		}
		else if (std::regex_search(line, matchR, reR) && matchR.size() > 1)
		{
			cycles = std::stoull(matchR.str(1), nullptr, 10);
			read = true;
			address = std::stoull(matchR.str(2), nullptr, 16);
		}
		else
		{
			SC_REPORT_FATAL(name(), "Syntax error in trace");
		}
#endif /* GCC_LESS_THAN_4_9_DOES_NOT_SUPPORT_REGEX */


		sc_time delay;

		if (sc_time_stamp() <= cycles * cycleTime)
		{
			delay = cycles * cycleTime - sc_time_stamp();
			//If the current simulation time is less than or equal to the expected time for the next cycle, calculate the delay to wait until that time.
		}
		else
		{
            delay = SC_ZERO_TIME;
		}

		trans.set_address(address);
		trans.set_data_length(4);
		trans.set_command(read ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);
		trans.set_data_ptr(data);
		iSocket->b_transport(trans, delay);

		wait(delay);

#if 1
		std::cout << std::setfill(' ') << std::setw(4)
			<< name() << " "
			<< std::setfill(' ') << std::setw(10)
			<< sc_time_stamp() << " "
			<< std::setfill(' ') << std::setw(5)
			<< (read ? "read" : "write") << " 0x"
			<< std::setfill('0') << std::setw(8)
			<< address
			<< " 0x" << std::hex
			<< std::setfill('0') << std::setw(2)
			<< (unsigned int)data[0]
			<< std::setfill('0') << std::setw(2)
			<< (unsigned int)data[1]
			<< std::setfill('0') << std::setw(2)
			<< (unsigned int)data[2]
			<< std::setfill('0') << std::setw(2)
			<< (unsigned int)data[3]
			<< std::endl;
#endif
	}

	// End Simulation because there are no events.
}



//The processRandom method generates random transactions and initiates TLM transactions based on the generated data.
void processor::processRandom()
{
    wait(SC_ZERO_TIME);

    tlm::tlm_generic_payload trans;

    uint64_t cycles;
    uint64_t address;
    unsigned char data[4];

    std::default_random_engine randGenerator;
    std::uniform_int_distribution<uint64_t> distrCycle(0, 99);
    std::uniform_int_distribution<uint64_t> distrAddr(0, 1023);

    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    
    trans.set_data_length(4);
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_data_ptr(data);

    for (uint64_t transId = 0; transId < 100000000; transId++)
    {
        cycles = distrCycle(randGenerator);
        address = distrAddr(randGenerator);

        //sc_time delay = cycles * cycleTime;
		//sc_time delay = SC_ZERO_TIME;
		//quantum keeper
        sc_time delay = quantumKeeper.get_local_time();   
        trans.set_address(address);
        iSocket->b_transport(trans, delay);

        //wait(delay);
		quantumKeeper.set(delay); // Anotate the time of the target
        quantumKeeper.inc(sc_time(10,SC_NS));

		if(quantumKeeper.need_sync())
        {
            quantumKeeper.sync();
        }

    }

    // End Simulation because there are no events.
}

#endif // PROCESSOR_H
