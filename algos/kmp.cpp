#include <iostream>
#include <vector>
//   	jjj jj          j           i
//	a	a	b	a	a	b	a	a	a	a	b	a	a	b	а	a	a	b
//	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18
//	0	1	0	1	2	3	4	5	2	2	3	4	5	6	7	8	9	3

std::vector<size_t> prefix_function (std::string s) 
{
    size_t n =  s.length();
	std::vector<size_t> pi(n); // в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для подстроки длины i. 
			 // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых 
    for (size_t i = 1; i < n; ++i) {
       // ищем, какой префикс-суффикс можно расширить
        size_t j = pi[i - 1]; // длина предыдущего префикса-суффикса, возможно нулевая
        while ((j > 0) && (s[i] != s[j])) // этот нельзя расширить,
            j = pi[j - 1];   // берем длину меньшего префикса-суффикса

        if (s[i] == s[j]) 
            ++j;  // расширяем найденный (возможно пустой) префикс-суффикс
        pi[i] = j;
     }
     return pi;
}

//    	 	            		                              
//	a	a	b	a	a			b	a	a	a	a	b	a	a	b	а	a	a	b
//	0	1	2	3	4			0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18
//	0	1	0	1	2			    

std::vector<size_t> kmp (std::string needle, std::string haystack) 
{
    size_t n =  haystack.length();
    size_t len =  needle.length();
	/* std::cout << len << " len \n"; */
	std::vector<size_t> pi = prefix_function(needle);
    std::vector<size_t> entries;
	/* std::cout << needle << std::endl; */ 
	/* for (int i; i < n; i++) */
	/* 	std::cout << i; */
	/* std::cout << std::endl; */
	/* for (std::vector<size_t>::iterator p = pi.begin(); p != pi.end(); p++) */
	/* 	std::cout << *p; */
    size_t j = 0; 
    for (size_t i = 0; i < n; ++i) {
		/* std::cout << j << "\n"; */
        while ((j > 0) && (haystack[i] != needle[j])) {
            j = pi[j - 1];  
		}
        if (haystack[i] == needle[j]) 
            ++j; 
		if (len == j) {
			/* std::cout << haystack.substr(i - (len-1), len) << " <" << '\n'; */	
			entries.push_back(i - (len-1));
			/* std::cout << i - len + 1 << '\n'; */	
			j--;
		}
     }
     return entries;
}

int main() {
	std::string needle("AABAA");
	std::string haystack("baaAABAAbaaaAABAAb");
    std::vector<size_t> entries = kmp(needle, haystack);
	for (std::vector<size_t>::iterator p = entries.begin(); p != entries.end(); p++)
		std::cout << haystack.substr(*p, needle.length()) << " <" << '\n';	
}

