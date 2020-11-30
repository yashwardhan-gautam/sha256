# SHA256
A small scaled version of SHA256 algorithm using C++, the program takes the hexadecimal equivalent of a text and produces its corresponding hash.
After the first 16 initial 32bit digits are found, next can be found using 

W(i) = Wⁱ⁻¹⁶ + σ⁰ + Wⁱ⁻⁷ + σ¹
where, 
 σ⁰ = (Wⁱ⁻¹⁵ ROTR⁷(x)) XOR (Wⁱ⁻¹⁵ ROTR¹⁸(x)) XOR (Wⁱ⁻¹⁵ SHR³(x))
 σ¹ = (Wⁱ⁻² ROTR¹⁷(x)) XOR (Wⁱ⁻² ROTR¹⁹(x)) XOR (Wⁱ⁻² SHR¹⁰(x))
 ROTRⁿ(x) = Circular right rotation of 'x' by 'n' bits
 SHRⁿ(x)  = Circular right shift of 'x' by 'n' bits
 
To find the hash, we use 6 initial hashes and 64 initial constants, which are :
a = 0x6a09e667
b = 0xbb67ae85
c = 0x3c6ef372
d = 0xa54ff53a
e = 0x510e527f
f = 0x9b05688c
g = 0x1f83d9ab
h = 0x5be0cd19
![alt text]()
