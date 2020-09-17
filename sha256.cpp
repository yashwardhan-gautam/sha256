#include<bits/stdc++.h>
typedef unsigned long long ll;

// Constants used in hash algorithm
const unsigned int K[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                          0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                          0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                          0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                          0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                          0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                          0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                          0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
                         };

std::vector<std::vector<unsigned int>> M; // Message to be hashed
std::vector<std::vector<unsigned int>> H; // Hashed message
std::vector<unsigned char> bytes;          // Plain and padded message bytes
unsigned int W[64];                       // Message schedule
ll l = 0;                         // Message length in bits
int N;                            // Number of blocks in padded message

unsigned int a, b, c, d, e, f, g, h;

unsigned int T1, T2;


// Take the given hexadecimal string and store the bytes in a global vector.
const void store_message_bytes(const std::string &hex_str)
{
	int str_length = hex_str.length();
	for (int i = 0, j = 0; i < str_length / 2; ++i, j += 2)
	{
		unsigned char byte = std::stoi(hex_str.substr(j, 2), nullptr, 16);
		bytes.push_back(byte);
		l += 8;
	}
}

// Calculate the required padding of the message.
const int calc_padding()
{
	int k = 0;
	while ((l + 1 + k) % 512 != 448) ++k;
	return k;
}

// Pad the message bytes
const void pad_message()
{
	int k = calc_padding();
	bytes.push_back(0x80);
	k = k - 7;
	for (int i = 0; i < (k / 8); ++i)
		bytes.push_back(0);
	for (int i = 1; i < 9; ++i)
		bytes.push_back(l >> (64 - i * 8));
}
const void parse_message()
{
	unsigned int n = 0;
	for (int i = 0; n < bytes.size() / 64; ++n)
	{
		std::vector<unsigned int> block(16);
		for (int j = 0; j < 16; ++j)
		{
			unsigned int word = 0;
			for (int k = 0; k < 4; ++k, ++i)
			{
				word <<= 8;
				word |= bytes[i];
			}
			block[j] = word;
		}
		M.push_back(block);
	}
	N = n;
}
const void init_hash()
{
	std::vector<unsigned int> h0 = {0x6a09e667,
	                                0xbb67ae85,
	                                0x3c6ef372,
	                                0xa54ff53a,
	                                0x510e527f,
	                                0x9b05688c,
	                                0x1f83d9ab,
	                                0x5be0cd19
	                               };
	H.push_back(h0);
}

// Rotate right function ROTR^n(x) in hash algorithm.
const unsigned int ROTR(const unsigned int &n, const unsigned int &x)
{
	return (x >> n) | (x << (32 - n));
}

// Right shift function SHR^n(x) in hash algorithm.
const unsigned int SHR(const unsigned int &n, const unsigned int &x)
{
	return x >> n;
}

// Logical function Ch(x, y, z) in hash algorithm.
const unsigned int Ch(const unsigned int &x, const unsigned int &y, const unsigned int &z)
{
	return (x & y) ^ (~x & z);
}

// Logical function Maj(x, y, z) in hash algorithm.
const unsigned int Maj(const unsigned int &x, const unsigned int &y, const unsigned int &z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

// Logical function (large) sigma^256_0(x) in hash algorithm.
const unsigned int lsigma0(const unsigned int &x)
{
	return ROTR(2, x) ^ ROTR(13, x) ^ ROTR(22, x);
}

// Logical function (large) sigma^256_1(x) in hash algorithm.
const unsigned int lsigma1(const unsigned int &x)
{
	return ROTR(6, x) ^ ROTR(11, x) ^ ROTR(25, x);
}

// Logical function (small) sigma^256_0(x) in hash algorithm.
const unsigned int ssigma0(const unsigned int &x)
{
	return ROTR(7, x) ^ ROTR(18, x) ^ SHR(3, x);
}

// Logical function (small) sigma^256_1(x) in hash algorithm.
const unsigned int ssigma1(const unsigned int &x)
{
	return ROTR(17, x) ^ ROTR(19, x) ^ SHR(10, x);
}


// Compute the hash value.
const void compute_hash()
{
	std::vector<unsigned int> hash_block(8);
	for (int i = 1; i <= N; ++i)
	{
		// Prepare message schedule
		for (int t = 0; t <= 15; ++t)
			W[t] = M[i - 1][t]; // M^i in spec
		for (int t = 16; t <= 63; ++t)
			W[t] = ssigma1(W[t - 2]) + W[t - 7] + ssigma0(W[t - 15]) + W[t - 16];

		// Initialise working variables with previous hash value
		a = H[i - 1][0];
		b = H[i - 1][1];
		c = H[i - 1][2];
		d = H[i - 1][3];
		e = H[i - 1][4];
		f = H[i - 1][5];
		g = H[i - 1][6];
		h = H[i - 1][7];

		// Perform logical operations
		for (int t = 0; t <= 63; ++t)
		{
			T1 = h + lsigma1(e) + Ch(e, f, g) + K[t] + W[t];
			T2 = lsigma0(a) + Maj(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		// Compute intermediate hash values by assigning them to H^i
		hash_block[0] = a + H[i - 1][0];
		hash_block[1] = b + H[i - 1][1];
		hash_block[2] = c + H[i - 1][2];
		hash_block[3] = d + H[i - 1][3];
		hash_block[4] = e + H[i - 1][4];
		hash_block[5] = f + H[i - 1][5];
		hash_block[6] = g + H[i - 1][6];
		hash_block[7] = h + H[i - 1][7];
		H.push_back(hash_block);
	}
}

//  Output the generated hash value as a hexadecimal string.
const void output_hash()
{
	// Concatenate the final hash blocks
	for (int i = 0; i < 8; ++i)
		std::cout << std::hex << std::setw(8) << std::setfill('0') << H[N][i];
	std::cout << std::endl;
}

// Clear all working vectors and variables.
const void clear()
{
	M.clear();
	H.clear();
	bytes.clear();
	l = 0;
}

int main()
{
	// Read each line as a hexadecimal string to be hashed
	for (std::string line; std::getline(std::cin, line);)
	{
		// Store the plain bytes of the message
		store_message_bytes(line);

		// Pad the bytes (if necessary)
		pad_message();

		// Parse message into word blocks
		parse_message();

		// Set the inital hash value
		init_hash();

		// Compute the hash value
		compute_hash();

		// Output the generated hash value
		output_hash();

		// Reset message to hash a new one
		clear();
	}
}