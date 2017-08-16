///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013 Academy of Motion Picture Arts and Sciences
// ("A.M.P.A.S."). Portions contributed by others as indicated.
// All rights reserved.
//
// A worldwide, royalty-free, non-exclusive right to copy, modify, create
// derivatives, and use, in source and binary forms, is hereby granted,
// subject to acceptance of this license. Performance of any of the
// aforementioned acts indicates acceptance to be bound by the following
// terms and conditions:
//
//  * Copies of source code, in whole or in part, must retain the
//    above copyright notice, this list of conditions and the
//    Disclaimer of Warranty.
//
//  * Use in binary form must retain the above copyright notice,
//    this list of conditions and the Disclaimer of Warranty in the
//    documentation and/or other materials provided with the distribution.
//
//  * Nothing in this license shall be deemed to grant any rights to
//    trademarks, copyrights, patents, trade secrets or any other
//    intellectual property of A.M.P.A.S. or any contributors, except
//    as expressly stated herein.
//
//  * Neither the name "A.M.P.A.S." nor the name of any other
//    contributors to this software may be used to endorse or promote
//    products derivative of or based on this software without express
//    prior written permission of A.M.P.A.S. or the contributors, as
//    appropriate.
//
// This license shall be construed pursuant to the laws of the State of
// California, and any disputes related thereto shall be subject to the
// jurisdiction of the courts therein.
//
// Disclaimer of Warranty: THIS SOFTWARE IS PROVIDED BY A.M.P.A.S. AND
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT ARE DISCLAIMED. IN NO
// EVENT SHALL A.M.P.A.S., OR ANY CONTRIBUTORS OR DISTRIBUTORS, BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, RESITUTIONARY,
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
// WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, THE ACADEMY
// SPECIFICALLY DISCLAIMS ANY REPRESENTATIONS OR WARRANTIES WHATSOEVER
// RELATED TO PATENT OR OTHER INTELLECTUAL PROPERTY RIGHTS IN THE ACADEMY
// COLOR ENCODING SYSTEM, OR APPLICATIONS THEREOF, HELD BY PARTIES OTHER
// THAN A.M.P.A.S., WHETHER DISCLOSED OR UNDISCLOSED.
///////////////////////////////////////////////////////////////////////////

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "../lib/mathOps.h"

using namespace std;

BOOST_AUTO_TEST_CASE ( Test_InvertD ) {
    double a = 1.0;
    BOOST_CHECK_CLOSE ( invertD(a), 1.0, 1e-9 );
    
    double b = 1000.0;
    BOOST_CHECK_CLOSE ( invertD(b), 0.001, 1e-9 );
    
    double c = 1000000.0;
    BOOST_CHECK_CLOSE ( invertD(c), 0.000001, 1e-9 );
};

BOOST_AUTO_TEST_CASE ( Test_Clip ) {
    double a = 254.9;
    BOOST_CHECK_CLOSE ( clip(a, 255.0), a, 1e-5 );
    
    double b = 255.1;
    BOOST_CHECK_CLOSE ( clip(b, 255.0), 255.0, 1e-5 );
    
    double c = 63355.0;
    BOOST_CHECK_CLOSE ( clip(c, 63355.0), c, 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_IsSquare ) {
    vector < vector < double > > a;
    a.resize(2);
    FORI(2) a[i].resize(2);
    BOOST_CHECK_EQUAL ( isSquare(a), 1 );
    
    FORI(2) a[i].resize(1);
    BOOST_CHECK_EQUAL ( isSquare(a), 0 );
};

BOOST_AUTO_TEST_CASE ( Test_Cross ) {
    double a[2] = { 1.0, 3.0 };
    double b[2] = { 1.0, 6.5 };
    
    vector < double > av(a, a+2);
    vector < double > bv(b, b+2);

    double cross_test = cross(av, bv);
    BOOST_CHECK_CLOSE ( cross_test, 3.50, 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_InvertVM ) {
    double M[3][3] = {
        { 0.0188205,  8.59E-03,   9.58E-03 },
        { 0.0440222,  0.0166118,  0.0258734 },
        { 0.1561591,  0.046321,   0.1181466 }
    };
    double M_Inverse[3][3] = {
        { -844.264597,  631.004958,  -69.728531 },
        { 1282.403375,  -803.858096,  72.055546 },
        { 613.114494,  -518.860936,  72.376689 }
    };
    
    vector < vector < double > > MV(3, vector < double > ( 3 ));
    FORIJ(3, 3) MV[i][j] = M[i][j];
    
    vector < vector < double > > MV_Inverse = invertVM (MV);
    
    FORI(3) {
        BOOST_CHECK_CLOSE ( MV_Inverse[i][0], M_Inverse[i][0], 1e-5 );
        BOOST_CHECK_CLOSE ( MV_Inverse[i][1], M_Inverse[i][1], 1e-5 );
        BOOST_CHECK_CLOSE ( MV_Inverse[i][2], M_Inverse[i][2], 1e-5 );
    }
};

BOOST_AUTO_TEST_CASE ( Test_DiagVM ) {
    double M[3][3] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 2.0, 0.0 },
        { 0.0, 0.0, 3.0 }
    };
    
    double vd[3] = { 1.0, 2.0, 3.0 };
    vector < double > MV(vd, vd+3);
    vector < vector < double > > MVD = diagVM (MV);
    
    FORI(3) {
        BOOST_CHECK_CLOSE ( MVD[i][0], M[i][0], 1e-5 );
        BOOST_CHECK_CLOSE ( MVD[i][1], M[i][1], 1e-5 );
        BOOST_CHECK_CLOSE ( MVD[i][2], M[i][2], 1e-5 );
    }
};

BOOST_AUTO_TEST_CASE ( Test_TransposeVec ) {
    double M[6][3] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 2.0, 0.0 },
        { 0.0, 0.0, 3.0 },
        { 1.0, 1.0, 2.0 },
        { 2.0, 2.0, 3.0 },
        { 3.0, 3.0, 4.0 }
    };

    double MT[3][6] = {
        { 1.0000000000,  0.0000000000,  0.0000000000,  1.0000000000,  2.0000000000,  3.0000000000 },
        { 0.0000000000,  2.0000000000,  0.0000000000,  1.0000000000,  2.0000000000,  3.0000000000 },
        { 0.0000000000,  0.0000000000,  3.0000000000,  2.0000000000,  3.0000000000,  4.0000000000 }
    };
    
    vector < vector < double > > MV(6, vector < double > ( 3 ));
    FORIJ(6, 3) MV[i][j] = M[i][j];
    vector < vector < double > > MVT = transposeVec (MV);
    
    FORIJ(3, 6)
        BOOST_CHECK_CLOSE ( MVT[i][j], MT[i][j], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_SumVector ) {
    double M[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    vector < double > MV(M, M+10);
    
    double sum = sumVector(MV);
    BOOST_CHECK_CLOSE ( sum, 55.0000, 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_ScaleVectorMax ) {
    double M[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double M_Scaled[10] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
    vector < double > MV(M, M+10);
    
    scaleVectorMax (MV);
    FORI(MV.size())
        BOOST_CHECK_CLOSE ( M_Scaled[i], MV[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_ScaleVectorMin ) {
    double M[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    vector < double > MV(M, M+10);
    
    scaleVectorMin (MV);
    FORI(MV.size())
        BOOST_CHECK_CLOSE ( M[i], MV[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_scaleVectorD ) {
    double M[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double M_Scaled[10] = { 10.0000000000,  5.0000000000,  3.3333333333,  2.5000000000,  2.0000000000,  1.6666666667,  1.4285714286,  1.2500000000,  1.1111111111,  1.0000000000 };
    vector < double > MV(M, M+10);
    
    scaleVectorD (MV);
    FORI(MV.size())
        BOOST_CHECK_CLOSE ( MV[i], M_Scaled[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_MulVectorElement ) {
    double M1[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double M2[10] = { 10.0000000000,  5.0000000000,  3.3333333333,  2.5000000000,  2.0000000000,  1.6666666667,  1.4285714286,  1.2500000000,  1.1111111111,  1.0000000000 };
    vector < double > MV1(M1, M1+10);
    vector < double > MV2(M2, M2+10);
    
    vector < double > MV3 = mulVectorElement ( MV1, MV2 );
    FORI(MV3.size())
        BOOST_CHECK_CLOSE ( MV3[i], 10.0000000000, 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_DivVectorElement ) {
    double M1[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double M2[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    
    vector < double > MV1(M1, M1+10);
    vector < double > MV2(M2, M2+10);
    
    vector < double > MV3 = divVectorElement ( MV1, MV2 );
    FORI(MV3.size())
        BOOST_CHECK_CLOSE ( MV3[i], 1.0000000000, 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_MulVector1 ) {
    double M1[3][3] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 2.0, 0.0 },
        { 0.0, 0.0, 3.0 }
    };
    double M2[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 0.5000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 0.3333333333 }
        
    };
    double M3[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 1.0000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 1.0000000000 }
        
    };
    
    vector < vector < double > > MV1( 3, vector < double > (3) );
    vector < vector < double > > MV2( 3, vector < double > (3) );
    FORIJ( 3, 3 ) {
        MV1[i][j] = M1[i][j];
        MV2[i][j] = M2[i][j];
    }
    
    vector < vector < double > > MV3 = mulVector ( MV1, MV2 );
    FORIJ( 3, 3 )
        BOOST_CHECK_CLOSE ( MV3[i][j], M3[i][j], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_MulVector2 ) {
    double M1[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 0.5000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 0.3333333333 }
        
    };
    double M2[3] = { 1.0000000000, 0.0000000000, 0.0000000000 };
    
    vector < vector < double > > MV1( 3, vector < double > (3) );
    vector < double > MV2( M2, M2+3 );
    FORIJ( 3, 3 ) {
        MV1[i][j] = M1[i][j];
    }
    
    vector < double > MV3 = mulVector ( MV1, MV2 );
    FORI ( 3 )
        BOOST_CHECK_CLOSE ( MV3[i], M2[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_MulVectorArray ) {
    double data[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double M[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 2.0000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 3.0000000000 }
        
    };
    
    double data_test[9] = { 1.0000000000,  4.0000000000,  9.0000000000,  4.0000000000, 10.0000000000, 18.0000000000,  7.0000000000, 16.0000000000, 27.0000000000 };

    vector < vector < double > > MV( 3, vector < double > (3) );
    FORIJ( 3, 3 )
        MV[i][j] = M[i][j];
    
    mulVectorArray( data, 9, 3, MV );
    FORI ( 9 )
        BOOST_CHECK_CLOSE ( data[i], data_test[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_SolveVM ) {
    double M1[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 2.0000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 3.0000000000 }
        
    };
    double M2[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 1.0000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 1.0000000000 }
        
    };
    
    double M3_test[3][3] = {
        { 1.0000000000, 0.0000000000, 0.0000000000 },
        { 0.0000000000, 0.5000000000, 0.0000000000 },
        { 0.0000000000, 0.0000000000, 0.3333333333 }
        
    };
    
    vector < vector < double > > MV1( 3, vector < double > (3) );
    vector < vector < double > > MV2( 3, vector < double > (3) );

    FORIJ( 3, 3 ) {
        MV1[i][j] = M1[i][j];
        MV2[i][j] = M2[i][j];
    }
    
    vector < vector < double > > MV3 = solveVM (MV1, MV2);
    FORIJ( 3, 3 )
        BOOST_CHECK_CLOSE ( MV3[i][j], M3_test[i][j], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_FindIndexInterp1 ) {
    int M[100];
    FORI(sizeof(M)/sizeof(int))
        M[i] = i * 2;

    vector < int > MV( M, M+100 );
    
    int index = findIndexInterp1 ( 100, MV, (int)MV.size() );
    BOOST_CHECK_EQUAL ( index, 50 );
};

BOOST_AUTO_TEST_CASE ( Test_Interp1DLinear ) {
    int X0[100], X1[100];
    double Y0[100];
    
    double Y1[100] = {
        0.0000000000,
        7.0000000000,
        14.0000000000,
        21.0000000000,
        28.0000000000,
        35.0000000000,
        42.0000000000,
        49.0000000000,
        56.0000000000,
        63.0000000000,
        70.0000000000,
        77.0000000000,
        84.0000000000,
        91.0000000000,
        98.0000000000,
        105.0000000000,
        112.0000000000,
        119.0000000000,
        126.0000000000,
        133.0000000000,
        140.0000000000,
        147.0000000000,
        154.0000000000,
        161.0000000000,
        168.0000000000,
        175.0000000000,
        182.0000000000,
        189.0000000000,
        196.0000000000,
        203.0000000000,
        210.0000000000,
        217.0000000000,
        224.0000000000,
        231.0000000000,
        238.0000000000,
        245.0000000000,
        252.0000000000,
        259.0000000000,
        266.0000000000,
        273.0000000000,
        280.0000000000,
        287.0000000000,
        294.0000000000,
        301.0000000000,
        308.0000000000,
        315.0000000000,
        322.0000000000,
        329.0000000000,
        336.0000000000,
        343.0000000000,
        350.0000000000,
        357.0000000000,
        364.0000000000,
        371.0000000000,
        378.0000000000,
        385.0000000000,
        392.0000000000,
        399.0000000000,
        406.0000000000,
        413.0000000000,
        420.0000000000,
        427.0000000000,
        434.0000000000,
        441.0000000000,
        448.0000000000,
        455.0000000000,
        462.0000000000,
        469.0000000000,
        476.0000000000,
        483.0000000000,
        490.0000000000,
        497.0000000000,
        504.0000000000,
        511.0000000000,
        518.0000000000,
        525.0000000000,
        532.0000000000,
        539.0000000000,
        546.0000000000,
        553.0000000000,
        560.0000000000,
        567.0000000000,
        574.0000000000,
        581.0000000000,
        588.0000000000,
        595.0000000000,
        602.0000000000,
        609.0000000000,
        616.0000000000,
        623.0000000000,
        630.0000000000,
        637.0000000000,
        644.0000000000,
        651.0000000000,
        658.0000000000,
        665.0000000000,
        672.0000000000,
        679.0000000000,
        686.0000000000,
        693.0000000000
    };
    
    
    FORI(100) {
        X0[i] = i;
        X1[i] = i * 2;
        Y0[i] = i * 3.5;
    }
    
    vector < int > XV0 ( X0, X0+100 );
    vector < int > XV1 ( X1, X1+100 );
    vector < double > YV0 ( Y0, Y0+100 );
    
    vector < double > YV1 = interp1DLinear ( XV0, XV1, YV0 );
    
    FORI(YV1.size())
        BOOST_CHECK_CLOSE ( YV1[i], Y1[i], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_XYZtoLAB ) {
    vector < vector < double > > XYZ ( 190, ( vector < double > ( 3 ) ));
    FORIJ(190, 3)
        XYZ [i][j] = 116 / (i * j + 1);
    vector < vector < double > > LAB_test = XYZtoLAB(XYZ);
    
    double LAB[190][3] = {
        { 549.7318794845,  39.7525650490,   2.8525942657 },
        { 433.0216903128,  542.8137252717,  103.7466920825 },
        { 373.9891471887,  797.2643421861,  105.2850850957 },
        { 340.3887517796,  942.0936327427,  111.9688202367 },
        { 313.8885696628,  1056.3185556598,  112.2268033081 },
        { 293.5345912517,  1144.0512212246,  104.0535371864 },
        { 276.3016835756,  1218.3309956907,  105.1382353663 },
        { 263.5765026443,  1273.1809134980,  100.5611044670 },
        { 249.5737042724,  1333.5378030323,  95.5244262891 },
        { 241.9816905060,  1366.2620003010,  82.4347473816 },
        { 233.9144240437,  1401.0347005697,  89.8919267762 },
        { 225.2897234740,  1438.2101340597,  75.0217533802 },
        { 216.0000000000,  1478.2520455856,  83.4482727113 },
        { 216.0000000000,  1478.2520455856,  83.4482727113 },
        { 205.9000172016,  1521.7864541994,  66.0345092658 },
        { 205.9000172016,  1521.7864541994,  94.9799053780 },
        { 194.7859887685,  1569.6917491695,  75.8177873900 },
        { 194.7859887685,  1569.6917491695,  75.8177873900 },
        { 194.7859887685,  1569.6917491695,  75.8177873900 },
        { 182.3572098145,  1623.2640722473,  90.7479168851 },
        { 182.3572098145,  1623.2640722473,  90.7479168851 },
        { 182.3572098145,  1623.2640722473,  90.7479168851 },
        { 182.3572098145,  1623.2640722473,  90.7479168851 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 168.1385220283,  1684.5515196015,  66.2329379434 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 151.3009501557,  1757.1272604319,  89.0348217657 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 130.1508417878,  1848.2915206382,  52.5691176832 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        { 100.0000000000,  1978.2520455856,  172.4137931034 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 },
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }, 
        {  0.0000000000,  2409.2865283442,   0.0000000000 }
    };
    
    FORIJ(190, 3)
        BOOST_CHECK_CLOSE ( LAB_test[i][j], LAB[i][j], 1e-5 );
};

BOOST_AUTO_TEST_CASE ( Test_GetCalcXYZt ) {
    vector < vector < double > > RGB ( 190, ( vector < double > ( 3 ) ));
    const double BStart[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    FORIJ(190, 3)
        RGB[i][j] = 10 / (i * j + 1);
    vector < vector < double > > XYZ_test = getCalcXYZt(RGB, BStart);
    
    double XYZ[190][3] = {
        {  9.5264607457, 10.0000000000, 10.0882518435 },
        {  9.5258049953,  6.8640973416,  3.0264755531 },
        {  9.5257113166,  5.4798976947,  2.0176503687 },
        {  9.5256176380,  4.8238641445,  1.0088251844 },
        {  9.5256176380,  4.8238641445,  1.0088251844 },
        {  9.5255239594,  4.1678305943,  0.0000000000 },
        {  9.5255239594,  4.1678305943,  0.0000000000 },
        {  9.5255239594,  4.1678305943,  0.0000000000 },
        {  9.5255239594,  4.1678305943,  0.0000000000 },
        {  9.5255239594,  4.1678305943,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 },
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }, 
        {  9.5255239594,  3.4396644977,  0.0000000000 }
    };
    
    FORIJ(190, 3)
        BOOST_CHECK_CLOSE ( XYZ_test[i][j], XYZ[i][j], 1e-5 );
};


