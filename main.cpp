#include <iostream>
#include "class.hpp"
int main()
{
   /*
   const SparseMatrix m_1(2, 2);
   const SparseMatrix m_2(2, 2);
   
   if (m_1 == m_2)
   {
       std::cout << "TRUE_1" << std::endl;
   }
   else
   {
       std::cout << "FALSE_1" << std::endl;
   }
   
   if (m_1 != m_2)
   {
       std::cout << "TRUE_2" << std::endl;
   }
   else
   {
       std::cout << "FALSE_2" << std::endl;
   }
   */
   /*
   const SparseMatrix m3(2, 2);
   const SparseMatrix m4 = m3;
   */
   //const SparseMatrix m5(2,2);
   //const SparseMatrix m6(2,2);
   //SparseMatrix m7 = m5+m6;
   /*
   SparseMatrix m8(2,2);
   m8[0][0] = 0;
   */
   /*
   const SparseMatrix m9(2,2);
   std::cout << "1" << " " << "1" << " " << m9[1][1] << std::endl;
   */
   /*
   SparseMatrix m10(2,2);
   *(*(m10+1)+1) = 8;
   std:: cout << std::endl;
   std::cout << "1" << " " << "1" << " " << m10[1][1] << std::endl;
   */
   /*
   const SparseMatrix m11(2,2);
   std:: cout << std::endl;
   std::cout << "1" << " " << "1" << " " << *(*(m11+1)+1) << std::endl;
   */
   /*
   SparseMatrix m11(2,3);
   SparseMatrix m12(3,2);
   SparseMatrix m13 = m11*m12;
   std::cout << std::endl;
   SparseMatrix m14(2,2);
   std::cout << std::endl;
   */
   /*
   const SparseMatrix m15(2,2);
   const SparseMatrix m16(2,2);
   const SparseMatrix m17 = m15*m16;
   std::cout << "0" << " " << "0" << " " << m17[0][0] << std::endl;
   */
   const SparseMatrix m18(2,2);
   const SparseMatrix m19(2,2);
   SparseMatrix m20 = m18+m19;
   //m18.set(0, 1, 3);
   //m20[0][0] = 3;
   //std::cout << "m20.nonzero_cnt = " << m20.nonzero_cnt << std::endl;
   m20.set(0, 0, 6);
   m20.set(0, 1, 7);
   std::cout << *(*(m20+0)+0) << " " << *(*(m20+0)+1) << " "<< *(*(m20+1)+0) << " " << *(*(m20+1)+1) << std::endl;
   return 0;
}
