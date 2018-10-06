/****************************************
 *  @file     IP_networks.cpp
 *  @brief	  compute the network address
 *		      and network mask based on a
 *		      given bunch of IP addresses
 *
 *---------------------------------------
 *  Details.
 *---------------------------------------
 *  @author	  HausinLynn
 *  @email    linhx36@mail2.sysu.edu.cn
 *  @version  1.0.0.1
 *  @date     10/04/2018
 *---------------------------------------
 *
 *---------------------------------------
 *  Change History
 *  <date>     | <version> | <author>
 *---------------------------------------
 *  10/04/2018 | 1.0.0.1   | HausinLynn
 *---------------------------------------
 *
 ***************************************/

/// System Headers
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

/// unsigned integer
typedef unsigned int uint;

/**
 * @brief	compute the network mask based on
 *			a given bunch of IP addresses
 *
 * @param   IP_addresses  --  a bunch of IP addresses
 * @param   num_of_IP     --  quantity of IP addresses
 *
 * @return  uint	network mask of the bunch of IPs
 */
uint get_mask(uint IP_addresses[], int num_of_IP) {
	uint temp_code = 0;    //!< temporary code
	
	/* some locations' bits in each IP addresses are the same,
	 * where temp_code's bits will be zero.
	 * other locations' bits in each IP addresses are arbitrary,
	 * where temp_code's bits will be one.
	 */
	for (int i = 0; i < num_of_IP - 1; i++) {
		temp_code |= IP_addresses[i] ^ IP_addresses[i+1];
	}
	
	/* compute how many last bits in each IP addresses are not same */
	int num_diff_bit = 0;
	while(temp_code > 0) {
		temp_code >>= 1;
		num_diff_bit++;
	}
	
	/* those location's bits, not same in each IP addresses, are zero in mask */
	uint mask = 0xffffffff << num_diff_bit;
	return mask;
}

/**
 * @brief	 output a 4-bytes address to file
 *
 * @param    output  --  file to output
 * @param    address --  an address need to output to file
 */
void file_print(ofstream &output, uint address) {
	uint byte0, byte1, byte2, byte3;

	byte0 = (address & 0xff000000) >> 24;	//!< first byte of address
	byte1 = (address & 0x00ff0000) >> 16;	//!< second byte of address
	byte2 = (address & 0x0000ff00) >>  8;	//!< third byte of address
	byte3 = (address & 0x000000ff) >>  0;	//!< last byte of address

	output << byte0 << '.';
	output << byte1 << '.';
	output << byte2 << '.';
	output << byte3 << endl;
}

/**
 * @brief	IP network main function
 *
 * @param   argc  --  counts of argument
 * @param   argv  --  variables of argument
 *
 * @return  integer
 */
int main(int argc, char** argv) {
	/* open input file */
	string filename;
	cout << "Please input the file name: " << endl;
	cin >> filename;
	ifstream input_file;
	input_file.open(filename);
	
	int num_of_IP;    //!< quantity of IP addresses
	input_file >> num_of_IP;

	uint IP_addresses[num_of_IP];	//!< IP addresses
	
	/* get each IP addresses in file */
	for (int i = 0; i < num_of_IP; i++) {
		char IP[20];
		input_file >> IP;
		
		uint byte0, byte1, byte2, byte3;	//!< each bytes
		sscanf(IP, "%d.%d.%d.%d", &byte0, &byte1, &byte2, &byte3);
		
		IP_addresses[i]
		   	= (byte0 << 24) + (byte1 << 16) + (byte2 << 8) + (byte3);
	}

	uint network_mask = get_mask(IP_addresses, num_of_IP);    //!< network mask
	uint network_address = network_mask & IP_addresses[0];	  //!< network address
	
	/* output to file */
	ofstream output_file("output.txt");
	file_print(output_file, network_address);
	file_print(output_file, network_mask);

	cout << "file 'output.txt' is created, please open it to check the output." << endl;
	input_file.close();
	output_file.close();

	return 0;
}
