#include <iostream>
#include <immintrin.h>

#include"./AVX-bit-manipulation.h"


using namespace std;

// _mm256_testnzc_si256 _mm256_testz_si256 _mm256_testnzc_si256 Ive tried all of these and the weren't reliable for me i think i missunderstand how the worn but im not sure 
void Test(__m256i a, __m256i b){
	if (_mm256_extract_epi64(a, 3) != _mm256_extract_epi64(b, 3) | _mm256_extract_epi64(a, 2) != _mm256_extract_epi64(b, 2) | _mm256_extract_epi64(a, 1) != _mm256_extract_epi64(b, 1) | _mm256_extract_epi64(a, 0) != _mm256_extract_epi64(b, 0)){
		cout << "problem" << endl;
		cout << std::hex << _mm256_extract_epi64(a, 3) << " " << _mm256_extract_epi64(a, 2) << " " << _mm256_extract_epi64(a, 1) << " " << _mm256_extract_epi64(a, 0) << "\n";
		cout << std::hex << _mm256_extract_epi64(b, 3) << " " << _mm256_extract_epi64(b, 2) << " " << _mm256_extract_epi64(b, 1) << " " << _mm256_extract_epi64(b, 0) << "\n";
		exit(-1);
	}
}

int main(int argc, char const *argv[]){

	const __m256i Zero = _mm256_set_epi64x(0ULL,0ULL,0ULL,0ULL);
	const __m256i LOne = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);
	const __m256i ROne = _mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL);
	const __m256i One4 = _mm256_set_epi64x(1ULL,1ULL,1ULL,1ULL);
	const __m256i Full = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF);
	const __m256i TestA = _mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555);
	const __m256i TestB = _mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA);
	const __m256i Test_64_0 = _mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF);
	const __m256i Test_64_1 = _mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0ULL);
	const __m256i Test_64_2 = _mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0ULL,0ULL);
	const __m256i Test_64_3 = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL);

// Tests for Logical left shift
	// Test the 64 bit shifts
	Test(_mm256_lls_mm256(Test_64_0,64),Test_64_1);
	Test(_mm256_lls_mm256(Test_64_0,128),Test_64_2);
	Test(_mm256_lls_mm256(Test_64_0,192),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_0,256),Zero);
	
	Test(_mm256_lls_mm256(Test_64_1,64),Test_64_2);
	Test(_mm256_lls_mm256(Test_64_1,128),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_1,192),Zero);

	Test(_mm256_lls_mm256(Test_64_2,64),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_2,128),Zero);

	Test(_mm256_lls_mm256(Test_64_3,64),Zero);

	// Test for the 1 bit shifts
	
	// Test A
	Test(_mm256_lls_mm256(TestA,1),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lls_mm256(TestA,2),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555554));
	Test(_mm256_lls_mm256(TestA,3),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAA8));
	Test(_mm256_lls_mm256(TestA,4),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555550));

	// Test B
	Test(_mm256_lls_mm256(TestB,1),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555554));
	Test(_mm256_lls_mm256(TestB,2),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAA8));
	Test(_mm256_lls_mm256(TestB,3),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555550));

	// Test Full
	Test(_mm256_lls_mm256(Full,1),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFE));
	Test(_mm256_lls_mm256(Full,2),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFC));
	Test(_mm256_lls_mm256(Full,3),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF8));
	Test(_mm256_lls_mm256(Full,4),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF0));
	Test(_mm256_lls_mm256(Full,5),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFE0));
	Test(_mm256_lls_mm256(Full,6),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFC0));
	Test(_mm256_lls_mm256(Full,7),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF80));
	Test(_mm256_lls_mm256(Full,8),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF00));

	Test(_mm256_lls_mm256(Full,56),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFF00000000000000));
	Test(_mm256_lls_mm256(Full,57),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFE00000000000000));
	Test(_mm256_lls_mm256(Full,58),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFC00000000000000));
	Test(_mm256_lls_mm256(Full,59),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xF800000000000000));
	Test(_mm256_lls_mm256(Full,60),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xF000000000000000));
	Test(_mm256_lls_mm256(Full,61),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xE000000000000000));
	Test(_mm256_lls_mm256(Full,62),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xC000000000000000));
	Test(_mm256_lls_mm256(Full,63),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0x8000000000000000));

	Test(_mm256_lls_mm256(Full,64),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL));

	Test(_mm256_lls_mm256(Full,65),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFE,0ULL));
	Test(_mm256_lls_mm256(Full,66),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFC,0ULL));
	Test(_mm256_lls_mm256(Full,67),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF8,0ULL));
	Test(_mm256_lls_mm256(Full,68),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF0,0ULL));
	Test(_mm256_lls_mm256(Full,69),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFE0,0ULL));
	Test(_mm256_lls_mm256(Full,70),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFC0,0ULL));
	Test(_mm256_lls_mm256(Full,71),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF80,0ULL));
	Test(_mm256_lls_mm256(Full,72),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF00,0ULL));

	Test(_mm256_lls_mm256(Full,120),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFF00000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,121),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFE00000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,122),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFC00000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,123),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xF800000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,124),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xF000000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,125),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xE000000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,126),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xC000000000000000,0ULL));
	Test(_mm256_lls_mm256(Full,127),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0x8000000000000000,0ULL));

	Test(_mm256_lls_mm256(Full,128),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL,0ULL));

	Test(_mm256_lls_mm256(Full,129),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFE,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,130),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFC,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,131),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF8,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,132),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF0,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,133),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFE0,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,134),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFC0,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,135),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF80,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,136),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF00,0ULL,0ULL));

	Test(_mm256_lls_mm256(Full,184),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFF00000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,185),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFE00000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,186),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFC00000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,187),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xF800000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,188),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xF000000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,189),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xE000000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,190),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xC000000000000000,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,191),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0x8000000000000000,0ULL,0ULL));

	Test(_mm256_lls_mm256(Full,192),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL));

	Test(_mm256_lls_mm256(Full,193),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFE,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,194),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFC,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,195),_mm256_set_epi64x(0xFFFFFFFFFFFFFFF8,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,196),_mm256_set_epi64x(0xFFFFFFFFFFFFFFF0,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,197),_mm256_set_epi64x(0xFFFFFFFFFFFFFFE0,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,198),_mm256_set_epi64x(0xFFFFFFFFFFFFFFC0,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,199),_mm256_set_epi64x(0xFFFFFFFFFFFFFF80,0ULL,0ULL,0ULL));
	Test(_mm256_lls_mm256(Full,200),_mm256_set_epi64x(0xFFFFFFFFFFFFFF00,0ULL,0ULL,0ULL));

	Test(_mm256_lls_mm256(Full,265),Zero);
	Test(_mm256_lls_mm256(Full,1000),Zero);
	Test(_mm256_lls_mm256(Full,10000),Zero);
	Test(_mm256_lls_mm256(Full,100000),Zero);
	Test(_mm256_lls_mm256(Full,1000000),Zero);
	Test(_mm256_lls_mm256(Full,999999999),Zero);
	Test(_mm256_lls_mm256(Full,0x7FFFFFFF),Zero);
	

	Test(_mm256_lls_mm256(Full,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test(_mm256_lls_64(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL));
	Test(_mm256_lls_128(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL,0ULL));
	Test(_mm256_lls_192(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(TestA),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0ULL));
	Test(_mm256_lls_128(TestA),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0ULL,0ULL));
	Test(_mm256_lls_192(TestA),_mm256_set_epi64x(0x5555555555555555,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL));
	Test(_mm256_lls_128(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL,0ULL));
	Test(_mm256_lls_192(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0ULL,0ULL,0ULL));


	Test(_mm256_lls_64(LOne),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test(_mm256_lls_128(LOne),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lls_192(LOne),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(One4),_mm256_set_epi64x(1ULL,1ULL,1ULL,0ULL));
	Test(_mm256_lls_128(One4),_mm256_set_epi64x(1ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lls_192(One4),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));
	cout << "LLS Passed" << endl;
	
	// Tests for Logical Right shift
	// Test the 64 bit shifts

	Test(_mm256_lrs_mm256(Test_64_3,64),Test_64_2);
	Test(_mm256_lrs_mm256(Test_64_3,128),Test_64_1);
	Test(_mm256_lrs_mm256(Test_64_3,192),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_3,256),Zero);
	
	Test(_mm256_lrs_mm256(Test_64_2,64),Test_64_1);
	Test(_mm256_lrs_mm256(Test_64_2,128),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_2,192),Zero);

	Test(_mm256_lrs_mm256(Test_64_1,64),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_1,128),Zero);

	Test(_mm256_lrs_mm256(Test_64_0,64),Zero);

	// Test for the 1 bit shifts
	
	// Test A
	Test(_mm256_lrs_mm256(TestA,1),_mm256_set_epi64x(0x2AAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_mm256(TestA,2),_mm256_set_epi64x(0x1555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_mm256(TestA,3),_mm256_set_epi64x(0x0AAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_mm256(TestA,4),_mm256_set_epi64x(0x0555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555));

	// Test B
	Test(_mm256_lrs_mm256(TestB,1),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_mm256(TestB,2),_mm256_set_epi64x(0x2AAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_mm256(TestB,3),_mm256_set_epi64x(0x1555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555));

	// Test Full
	Test(_mm256_lrs_mm256(Full,1),_mm256_set_epi64x(0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,2),_mm256_set_epi64x(0x3FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,3),_mm256_set_epi64x(0x1FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,4),_mm256_set_epi64x(0x0FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,5),_mm256_set_epi64x(0x07FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,6),_mm256_set_epi64x(0x03FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,7),_mm256_set_epi64x(0x01FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,8),_mm256_set_epi64x(0x00FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	
	Test(_mm256_lrs_mm256(Full,56),_mm256_set_epi64x(0x00000000000000FF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,57),_mm256_set_epi64x(0x000000000000007F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,58),_mm256_set_epi64x(0x000000000000003F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,59),_mm256_set_epi64x(0x000000000000001F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,60),_mm256_set_epi64x(0x000000000000000F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,61),_mm256_set_epi64x(0x0000000000000007,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,62),_mm256_set_epi64x(0x0000000000000003,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,63),_mm256_set_epi64x(0x0000000000000001,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,64),_mm256_set_epi64x(0ULL, 0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,65),_mm256_set_epi64x(0ULL, 0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,66),_mm256_set_epi64x(0ULL, 0x3FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,67),_mm256_set_epi64x(0ULL, 0x1FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,68),_mm256_set_epi64x(0ULL, 0x0FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,69),_mm256_set_epi64x(0ULL, 0x07FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,70),_mm256_set_epi64x(0ULL, 0x03FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,71),_mm256_set_epi64x(0ULL, 0x01FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,72),_mm256_set_epi64x(0ULL, 0x00FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,120),_mm256_set_epi64x(0ULL, 0x00000000000000FF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,121),_mm256_set_epi64x(0ULL, 0x000000000000007F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,122),_mm256_set_epi64x(0ULL, 0x000000000000003F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,123),_mm256_set_epi64x(0ULL, 0x000000000000001F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,124),_mm256_set_epi64x(0ULL, 0x000000000000000F,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,125),_mm256_set_epi64x(0ULL, 0x0000000000000007,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,126),_mm256_set_epi64x(0ULL, 0x0000000000000003,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,127),_mm256_set_epi64x(0ULL, 0x0000000000000001,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,128),_mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,129),_mm256_set_epi64x(0ULL, 0ULL, 0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,130),_mm256_set_epi64x(0ULL, 0ULL, 0x3FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,131),_mm256_set_epi64x(0ULL, 0ULL, 0x1FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,132),_mm256_set_epi64x(0ULL, 0ULL, 0x0FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,133),_mm256_set_epi64x(0ULL, 0ULL, 0x07FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,134),_mm256_set_epi64x(0ULL, 0ULL, 0x03FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,135),_mm256_set_epi64x(0ULL, 0ULL, 0x01FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,136),_mm256_set_epi64x(0ULL, 0ULL, 0x00FFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,184),_mm256_set_epi64x(0ULL, 0ULL, 0x00000000000000FF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,185),_mm256_set_epi64x(0ULL, 0ULL, 0x000000000000007F,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,186),_mm256_set_epi64x(0ULL, 0ULL, 0x000000000000003F,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,187),_mm256_set_epi64x(0ULL, 0ULL, 0x000000000000001F,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,188),_mm256_set_epi64x(0ULL, 0ULL, 0x000000000000000F,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,189),_mm256_set_epi64x(0ULL, 0ULL, 0x0000000000000007,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,190),_mm256_set_epi64x(0ULL, 0ULL, 0x0000000000000003,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,191),_mm256_set_epi64x(0ULL, 0ULL, 0x0000000000000001,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,192),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,193),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x7FFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,194),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x3FFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,195),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x1FFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,196),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x0FFFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,197),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x07FFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,198),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x03FFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,199),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x01FFFFFFFFFFFFFF));
	Test(_mm256_lrs_mm256(Full,200),_mm256_set_epi64x(0ULL, 0ULL, 0ULL, 0x00FFFFFFFFFFFFFF));

	Test(_mm256_lrs_mm256(Full,265),Zero);
	Test(_mm256_lrs_mm256(Full,1000),Zero);
	Test(_mm256_lrs_mm256(Full,10000),Zero);
	Test(_mm256_lrs_mm256(Full,100000),Zero);
	Test(_mm256_lrs_mm256(Full,1000000),Zero);
	Test(_mm256_lrs_mm256(Full,999999999),Zero);
	Test(_mm256_lrs_mm256(Full,0x7FFFFFFF),Zero);
	

	Test(_mm256_lrs_mm256(Full,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test(_mm256_lrs_64(Full),_mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_128(Full),_mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_192(Full),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_64(TestA),_mm256_set_epi64x(0ULL,0x5555555555555555,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_128(TestA),_mm256_set_epi64x(0ULL,0ULL,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_192(TestA),_mm256_set_epi64x(0ULL,0ULL,0ULL,0x5555555555555555));

	Test(_mm256_lrs_64(TestB),_mm256_set_epi64x(0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_128(TestB),_mm256_set_epi64x(0ULL,0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_192(TestB),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xAAAAAAAAAAAAAAAA));

	Test(_mm256_lrs_64(ROne),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lrs_128(ROne),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test(_mm256_lrs_192(ROne),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));

	Test(_mm256_lrs_64(One4),_mm256_set_epi64x(0ULL,1ULL,1ULL,1ULL));
	Test(_mm256_lrs_128(One4),_mm256_set_epi64x(0ULL,0ULL,1ULL,1ULL));
	Test(_mm256_lrs_192(One4),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));


	cout << "LRS Passed" << endl;
	
	return 0;
}