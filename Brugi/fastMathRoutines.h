
//***************************************************************
// contrain function for 32-bit values
//***************************************************************
inline int32_t constrain_int32(int32_t x , int32_t l, int32_t h) {
  if (x <= l) {
    return l;
  } else if (x >= h) {
    return h;
  } else {
    return x;
  }
}

//***************************************************************
// “Efficient approximations for the arctangent function”,
// Rajan, S. Sichun Wang Inkol, R. Joyal, A., May 2006
//***************************************************************
inline float Rajan_FastArcTan(float x) {
  return PI/4.0*x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}

// atan2 for all quadrants by A. Hahn
inline float Rajan_FastArcTan2(float y, float x) {

  uint8_t qCode;
  const float pi_2 = PI/2.0;
  float q;
  float z;

  // 6 us
  bool swap45 = (fabs(y) > fabs(x));
    
  // 22us
  if ((y >= 0) && (x >= 0)) { qCode = 0; }
  if ((y >= 0) && (x <= 0)) { qCode = 1; }
  if ((y <= 0) && (x <= 0)) { qCode = 2; }
  if ((y <= 0) && (x >= 0)) { qCode = 3; }

  // 54 us
  if (swap45) {
    q = x / y;
  } else {
    q = y / x;
  }

  // 92 us
  z = Rajan_FastArcTan(q);

  if (swap45) {
    switch (qCode) {
      case 0: z = pi_2 - z;  break;
      case 1: z = pi_2 - z;  break;
      case 2: z = -pi_2 - z; break;
      case 3: z = -pi_2 - z; break;
    }
  } else {
    switch (qCode) {    
      case 0: z = z;         break;
      case 1: z = PI + z;    break;
      case 2: z = -PI + z;   break;
      case 3: z = z;         break;
    }
  }
  
  return z;
}

// atan2 returnig degrees * 1000
int32_t Rajan_FastArcTan2_deg1000(float y, float x) {
  return 180/PI * 1000 * Rajan_FastArcTan2(y, x);
}


/************************/
/* LP Filter            */
/************************/
inline void utilLP_float(float * q, float i, float coeff) {
  *q += (i - *q) * coeff; // faster version on ATmega
  //*q = *q * (1.0f-coeff) + i * coeff;
}

//************************
// low pass 3rd order
//************************
float utilLP3_float(float * q, float i, float coeff) {

  utilLP_float(&q[2], i, coeff);
  utilLP_float(&q[1], q[2], coeff);
  utilLP_float(&q[0], q[1], coeff);
  return q[0];
  
}


/*
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 * Thanks to
 * http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 *
 */
 
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc crcSlow(uint8_t const message[], int nBytes)
{
    crc  remainder = 0;	


    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (int byte = 0; byte < nBytes; ++byte)
    {
      
        /*
         * Bring the next byte into the remainder.
         */
        remainder ^= (message[byte] << (WIDTH - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /*
     * The final remainder is the CRC result.
     */
    return (remainder);

}   /* crcSlow() */
