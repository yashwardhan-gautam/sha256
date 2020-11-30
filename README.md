# SHA256
A small scaled version of SHA256 algorithm using C++, the program takes the hexadecimal equivalent of a text and produces its corresponding hash.
After the first 16digits initial 32bit digits are found, next (64-16)digits can be found using \
\
W(i) = Wⁱ⁻¹⁶ + σ⁰ + Wⁱ⁻⁷ + σ¹\
where, \
 σ⁰ = (Wⁱ⁻¹⁵ ROTR⁷(x)) XOR (Wⁱ⁻¹⁵ ROTR¹⁸(x)) XOR (Wⁱ⁻¹⁵ SHR³(x))\
 σ¹ = (Wⁱ⁻² ROTR¹⁷(x)) XOR (Wⁱ⁻² ROTR¹⁹(x)) XOR (Wⁱ⁻² SHR¹⁰(x))\
 ROTRⁿ(x) = Circular right rotation of 'x' by 'n' bits \
 SHRⁿ(x)  = Circular right shift of 'x' by 'n' bits\
 
To find the hash, we use 6 initial hashes and 64 initial constants, which are : \
A = 0x6a09e667\
B = 0xbb67ae85\
C = 0x3c6ef372\
D = 0xa54ff53a\
E = 0x510e527f\
F = 0x9b05688c\
G = 0x1f83d9ab\
H = 0x5be0cd19\
![64 constants](https://github.com/yashwardhan-gautam/sha256/blob/master/1_GNXx6NbFolhTKx_C7awdeg.png)\
Then we run the final step using all of this\
![Final State](https://github.com/yashwardhan-gautam/sha256/blob/master/im2.png)  
Ch(E, F, G) = (E AND F) XOR ((NOT E) AND G)\
Ma(A, B, C) = (A AND B) XOR (A AND C) XOR (B AND C)\
    ∑(A)    = (A >>> 2) XOR (A >>> 13) XOR (A >>> 22)\
    ∑(E)    = (E >>> 6) XOR (E >>> 11) XOR (E >>> 25)+\
            = addition modulo 2³²
