class CHSInt128
{ 
public: 
	int	m_A;												// Low 32 Bit 
	int	m_B; 
	int	m_C;	 
	int	m_D;												// Heigh 32 Bit 
 
public: 
	CHSInt128		( const int		 nValue  ); 
	CHSInt128		( const long	 lValue  ); 
	CHSInt128		( const __int64& nnValue ); 
	CHSInt128		( const int	 uValue  ); 
	CHSInt128		( const int	 dwValue ); 
	CHSInt128		( const unsigned long long&	 nnValue ); 
	CHSInt128		( const CHSInt128& iValue  ); 
	CHSInt128		(); 
	virtual			~CHSInt128(); 
 
	bool			ToStr		( CString& strValue ); 
	bool			FromStr		( LPCTSTR lpszValue ); 
	CHSInt128&		operator=	( const CHSInt128& iValue ); 
	 
	CHSInt128		operator-	( const CHSInt128& iValue );	// const; 
	CHSInt128&		operator-=	( const CHSInt128& iValue ); 
	CHSInt128		operator+	( const CHSInt128& iValue );	// const; 
	CHSInt128&		operator+=	( const CHSInt128& iValue ); 
	CHSInt128		operator*	( const CHSInt128& iValue ) const; 
	CHSInt128&		operator*=	( const CHSInt128& iValue ); 
	CHSInt128		operator/	( const CHSInt128& iValue ) const; 
	CHSInt128&		operator/=	( const CHSInt128& iValue ); 
	CHSInt128		operator%	( const CHSInt128& iValue ) const; 
	CHSInt128&		operator%=	( const CHSInt128& iValue ); 
 
	CHSInt128&		operator++	( void );						// ++n		 
	CHSInt128&		operator--	( void );						// --n	 
	CHSInt128		operator++	( int );						// n++			 
	CHSInt128		operator--	( int );						// n-- 
 
	CHSInt128		operator^	( const CHSInt128& iValue ) const; 
	CHSInt128		operator&	( const CHSInt128& iValue ) const; 
	CHSInt128		operator|	( const CHSInt128& iValue ) const; 
	CHSInt128		operator~	( void ) const; 
 
	CHSInt128&		operator^=	( const CHSInt128& iValue ); 
	CHSInt128&		operator&=	( const CHSInt128& iValue ); 
	CHSInt128&		operator|=	( const CHSInt128& iValue ); 
 
	CHSInt128		operator<< 	( const int nShift ); 
	CHSInt128&		operator<<= ( const int nShift ); 
	CHSInt128		operator>>  ( const int nShift ); 
	CHSInt128&		operator>>= ( const int nShift ); 
 
	bool			operator==	( const CHSInt128& iValue ) const; 
	bool			operator!=	( const CHSInt128& iValue ) const; 
	bool			operator>	( const CHSInt128& iValue ) const; 
	bool			operator<	( const CHSInt128& iValue ) const; 
	bool			operator>=	( const CHSInt128& iValue ) const; 
	bool			operator<=	( const CHSInt128& iValue ) const; 

	void			SetPositiveFlag	 ( void ); 
	void			SetNegativeFlag	 ( void ); 
	void			Complement		 ( void ); 
	void			ComplementInverse( void ); 
	void			Min				 ( void ); 
	void			Max				 ( void ); 
	void			Zero			 ( void ); 
	void			SetAt			 ( int uIndex, bool bSet ); 
 
	bool			IsZero			 ( void ) const; 
	bool			IsNegative		 ( void ) const; 
	bool			IsPositive		 ( void ) const; 
	bool			GetAt			 ( int uIndex ) const; 
	CHSInt128		GetRight		 ( int uCount ) const; 
	CHSInt128		GetLeft			 ( int uCount ) const; 
 
	void		Division			 ( const CHSInt128& iDivisor, CHSInt128& iQuotient, CHSInt128& iRemainder) const; 
 
}; 
 

// Default
CHSInt128::CHSInt128() {
    m_A = m_B = m_C = m_D = 0;
}

CHSInt128::~CHSInt128() {
}

// unsigned int
CHSInt128::CHSInt128(const int uValue) {
    *this = CHSInt128((int)uValue);
}

// int
CHSInt128::CHSInt128(const int nValue) {
    if (nValue < 0) {
        *this = CHSInt128(int(-nValue));
        Complement();
    } else {
        *this = CHSInt128((int)nValue);
    }
}

// unsigned long
CHSInt128::CHSInt128(const int dwValue) {
    m_D = m_B = m_C = 0;

    m_A = dwValue;
}

// long
CHSInt128::CHSInt128(const long lValue) {
    if (lValue < 0) {
        *this = CHSInt128((int)(-lValue));
        Complement();
    } else {
        *this = CHSInt128((int)lValue);
    }
}

// unsigned __int64
CHSInt128::CHSInt128(const unsigned long long &nnValue) {
    m_D = m_C = 0;

    m_B = HI32(nnValue);
    m_A = LO32(nnValue);
}

// __int64
CHSInt128::CHSInt128(const __int64 &nnValue) {
    if (nnValue < 0) {
        *this = CHSInt128((unsigned long long)(-nnValue));
        Complement();
    } else {
        *this = CHSInt128((unsigned long long)nnValue);
    }
}

// CHSInt128
CHSInt128::CHSInt128(const CHSInt128 &iValue) {
    m_A = iValue.m_A;
    m_B = iValue.m_B;
    m_C = iValue.m_C;
    m_D = iValue.m_D;
}

// Operator =
CHSInt128 &CHSInt128::operator=(const CHSInt128 &iValue) {
    m_A = iValue.m_A;
    m_B = iValue.m_B;
    m_C = iValue.m_C;
    m_D = iValue.m_D;

    return *this;
}

// Operator +
CHSInt128 CHSInt128::operator+(const CHSInt128 &iValue) {
    CHSInt128 iTemp;

    ADD(iTemp.m_A, m_A, iValue.m_A);
    ADC(iTemp.m_B, m_B, iValue.m_B);
    ADC(iTemp.m_C, m_C, iValue.m_C);
    ADC(iTemp.m_D, m_D, iValue.m_D);

    return iTemp;
}

// Operator ++n
CHSInt128 &CHSInt128::operator++() {
    *this = *this + CHSInt128(1);

    return *this;
}

// Operator n++
CHSInt128 CHSInt128::operator++(int) {
    CHSInt128 iTemp(*this);

    *this = *this + CHSInt128(1);

    return iTemp;
}

// Operator +=
CHSInt128 &CHSInt128::operator+=(const CHSInt128 &iValue) {
    *this = *this + iValue;

    return *this;
}

// Operator -
CHSInt128 CHSInt128::operator-(const CHSInt128 &iValue) {
    CHSInt128 iTemp;

    SUB(iTemp.m_A, m_A, iValue.m_A);
    SBB(iTemp.m_B, m_B, iValue.m_B);
    SBB(iTemp.m_C, m_C, iValue.m_B);
    SBB(iTemp.m_D, m_D, iValue.m_B);

    return iTemp;
}

// Operator --n
CHSInt128 &CHSInt128::operator--() {
    *this = *this - CHSInt128(1);

    return *this;
}

// Operator n--
CHSInt128 CHSInt128::operator--(int) {
    CHSInt128 iTemp(*this);

    *this = *this - CHSInt128(1);

    return iTemp;
}

// Operator -=
CHSInt128 &CHSInt128::operator-=(const CHSInt128 &iValue) {
    *this = *this - iValue;

    return *this;
}

// Operator &
CHSInt128 CHSInt128::operator&(const CHSInt128 &iValue) const {
    CHSInt128 iTemp;

    iTemp.m_A = m_A & iValue.m_A;
    iTemp.m_B = m_B & iValue.m_B;
    iTemp.m_C = m_C & iValue.m_C;
    iTemp.m_D = m_D & iValue.m_D;

    return iTemp;
}

// Operator &=
CHSInt128 &CHSInt128::operator&=(const CHSInt128 &iValue) {
    *this = *this & iValue;

    return *this;
}

// Operator |
CHSInt128 CHSInt128::operator|(const CHSInt128 &iValue) const {
    CHSInt128 iTemp;

    iTemp.m_A = m_A | iValue.m_A;
    iTemp.m_B = m_B | iValue.m_B;
    iTemp.m_C = m_C | iValue.m_C;
    iTemp.m_D = m_D | iValue.m_D;

    return iTemp;
}

// Operator |=
CHSInt128 &CHSInt128::operator|=(const CHSInt128 &iValue) {
    *this = *this | iValue;

    return *this;
}

// Operator ^
CHSInt128 CHSInt128::operator^(const CHSInt128 &iValue) const {
    CHSInt128 iTemp;

    iTemp.m_A = m_A ^ iValue.m_A;
    iTemp.m_B = m_B ^ iValue.m_B;
    iTemp.m_C = m_C ^ iValue.m_C;
    iTemp.m_D = m_D ^ iValue.m_D;

    return iTemp;
}

// Operator ^=
CHSInt128 &CHSInt128::operator^=(const CHSInt128 &iValue) {
    *this = *this ^ iValue;

    return *this;
}

// Operator ~
CHSInt128 CHSInt128::operator~() const {
    CHSInt128 iTemp;

    iTemp.m_A = ~m_A;
    iTemp.m_B = ~m_B;
    iTemp.m_C = ~m_C;
    iTemp.m_D = ~m_D;

    return iTemp;
}

// Operator <<
CHSInt128 CHSInt128::operator<<(const int uShift) {
    CHSInt128 iTemp(*this);

    int uShiftN = (uShift / 32);
    int uShiftL = (uShift % 32);

    for (int iN = 0; iN < uShiftN; iN++) {
        SHL(iTemp.m_D, 32);
        SHL(iTemp.m_D, iTemp.m_C, 32);
        SHL(iTemp.m_C, iTemp.m_B, 32);
        SHL(iTemp.m_B, iTemp.m_A, 32);
    }

    if (uShiftL > 0) {
        SHL(iTemp.m_D, uShiftL);
        SHL(iTemp.m_D, iTemp.m_C, uShiftL);
        SHL(iTemp.m_C, iTemp.m_B, uShiftL);
        SHL(iTemp.m_B, iTemp.m_A, uShiftL);
    }

    return iTemp;
}

// Operator <<=
CHSInt128 &CHSInt128::operator<<=(const int uShift) {
    *this = (*this << uShift);

    return *this;
}

// Operator >>
CHSInt128 CHSInt128::operator>>(const int uShift) {
    CHSInt128 iTemp(*this);

    int uShiftN = (uShift / 32);
    int uShiftL = (uShift % 32);

    for (int iN = 0; iN < uShiftN; iN++) {
        SHR(iTemp.m_A, 32);
        SHR(iTemp.m_B, iTemp.m_A, 32);
        SHR(iTemp.m_C, iTemp.m_B, 32);
        SHR(iTemp.m_D, iTemp.m_C, 32);
    }

    if (uShiftL > 0) {
        SHR(iTemp.m_A, uShiftL);
        SHR(iTemp.m_B, iTemp.m_A, uShiftL);
        SHR(iTemp.m_C, iTemp.m_B, uShiftL);
        SHR(iTemp.m_D, iTemp.m_C, uShiftL);
    }

    return iTemp;
}

// Operator >>=
CHSInt128 &CHSInt128::operator>>=(const int uShift) {
    *this = (*this >> uShift);

    return *this;
}

// Operator ==
bool CHSInt128::operator==(const CHSInt128 &iValue) const {
    return ((m_A == iValue.m_A) &&
            (m_B == iValue.m_B) &&
            (m_C == iValue.m_C) &&
            (m_D == iValue.m_D));
}

// Operator !=
bool CHSInt128::operator!=(const CHSInt128 &iValue) const {
    return ((m_A != iValue.m_A) ||
            (m_B != iValue.m_B) ||
            (m_C != iValue.m_C) ||
            (m_D != iValue.m_D));
}

// Operator >
bool CHSInt128::operator>(const CHSInt128 &iValue) const {
    if (m_D > iValue.m_D) return true;
    if (m_D < iValue.m_D) return false;

    if (m_C > iValue.m_C) return true;
    if (m_C < iValue.m_C) return false;

    if (m_B > iValue.m_B) return true;
    if (m_B < iValue.m_B) return false;

    if (m_A > iValue.m_A) return true;
    if (m_A < iValue.m_A) return false;

    return false;
}

// Operator >=
bool CHSInt128::operator>=(const CHSInt128 &iValue) const {
    return ((*this > iValue) || (*this == iValue));
}

// Operator <
bool CHSInt128::operator<(const CHSInt128 &iValue) const {
    if (m_D < iValue.m_D) return true;
    if (m_D > iValue.m_D) return false;

    if (m_C < iValue.m_C) return true;
    if (m_C > iValue.m_C) return false;

    if (m_B < iValue.m_B) return true;
    if (m_B > iValue.m_B) return false;

    if (m_A < iValue.m_A) return true;
    if (m_A > iValue.m_A) return false;

    return false;
}

// Operator <=
bool CHSInt128::operator<=(const CHSInt128 &iValue) const {
    return ((*this < iValue) || (*this == iValue));
}

// Operator *
CHSInt128 CHSInt128::operator*(const CHSInt128 &iValue) const {
    CHSInt128 iResult;

    CHSInt128 iT1(((unsigned long long)m_A) * ((unsigned long long)iValue.m_A));
    CHSInt128 iT2(((unsigned long long)m_B) * ((unsigned long long)iValue.m_A));
    CHSInt128 iT3(((unsigned long long)m_C) * ((unsigned long long)iValue.m_A));
    CHSInt128 iT4(((unsigned long long)m_D) * ((unsigned long long)iValue.m_A));

    iResult += iT1;
    iResult += (iT2 << 32);
    iResult += (iT3 << 64);
    iResult += (iT4 << 96);

    CHSInt128 iT5(((unsigned long long)m_A) * ((unsigned long long)iValue.m_B));
    CHSInt128 iT6(((unsigned long long)m_B) * ((unsigned long long)iValue.m_B));
    CHSInt128 iT7(((unsigned long long)m_C) * ((unsigned long long)iValue.m_B));

    iResult += (iT5 << 32);
    iResult += (iT6 << 64);
    iResult += (iT7 << 96);

    CHSInt128 iT8(((unsigned long long)m_A) * ((unsigned long long)iValue.m_C));
    CHSInt128 iT9(((unsigned long long)m_B) * ((unsigned long long)iValue.m_C));

    iResult += (iT8 << 64);
    iResult += (iT9 << 96);

    CHSInt128 iT0(((unsigned long long)m_A) * ((unsigned long long)iValue.m_D));

    iResult += (iT0 << 96);

    return iResult;
}

// Operator *=
CHSInt128 &CHSInt128::operator*=(const CHSInt128 &iValue) {
    *this = *this * iValue;

    return *this;
}

// Operator /
CHSInt128 CHSInt128::operator/(const CHSInt128 &iValue) const {
    CHSInt128 iQuotient;
    CHSInt128 iRemainder;

    Division(iValue, iQuotient, iRemainder);

    return iQuotient;
}

// Operator /=
CHSInt128 &CHSInt128::operator/=(const CHSInt128 &iValue) {
    *this = *this / iValue;

    return *this;
}

// Operator %
CHSInt128 CHSInt128::operator%(const CHSInt128 &iValue) const {
    CHSInt128 iQuotient;
    CHSInt128 iRemainder;

    Division(iValue, iQuotient, iRemainder);

    return iRemainder;
}

// Operator %=
CHSInt128 &CHSInt128::operator%=(const CHSInt128 &iValue) {
    *this = *this % iValue;

    return *this;
}

// Complement
void CHSInt128::Complement(void) {
    NOT(m_A);
    NOT(m_B);
    NOT(m_C);
    NOT(m_D);

    *this = *this + CHSInt128(1);
    ;
}

// Inverse Complement
void CHSInt128::ComplementInverse(void) {
    *this = *this - CHSInt128(1);
    ;

    NOT(m_A);
    NOT(m_B);
    NOT(m_C);
    NOT(m_D);
}

// If Value is Positive return true
bool CHSInt128::IsPositive(void) const {
    return ((m_D & 0X80000000) == 0X00000000);
}

// Return true, If its Negative
bool CHSInt128::IsNegative(void) const {
    return ((m_D & 0X80000000) == 0X80000000);
}

// Set Negative Flag
void CHSInt128::SetNegativeFlag(void) {
    OR(m_D, 0X80000000);
}

// Set Positive Flag
void CHSInt128::SetPositiveFlag(void) {
    AND(m_D, 0X7FFFFFFF);
}

// Division
void CHSInt128::Division(const CHSInt128 &iDivisor, CHSInt128 &iQuotient, CHSInt128 &iRemainder) const {
    if (iDivisor == CHSInt128(0)) {
        __asm
        {   
            mov eax, 0   
            div eax
        }
    }

    iQuotient.Zero();
    iRemainder.Zero();

    // 原码加减交替法计算 X/Y
    CHSInt128 iTempR0;            // R0 : Remainder
    CHSInt128 iTempR1(*this);     // R1 : Quotient
    CHSInt128 iTempR2(iDivisor);  // R2 : Divisor

    // if Dividend is Zero, No Need Calc
    if (iTempR1.IsZero()) return;

    bool bDivrNegative = false, bDivdNegative = false;

    // 将补码转换为原码
    if (iTempR1.IsNegative()) {
        iTempR1.ComplementInverse();
        bDivdNegative = true;
    } else
        iTempR1.SetAt(127, 0);

    // 将补码转换为原码
    if (iDivisor.IsNegative()) {
        iTempR2.ComplementInverse();
        bDivrNegative = true;
    } else
        iTempR2.SetAt(127, 0);

    iTempR0 -= iTempR2;

    for (int iN = 0; iN < 128; iN++) {
        iTempR0 <<= 1;

        // Move iTempR1(High Bit) to iTempR0(Low Bit)
        if (iTempR1.GetAt(127))
            iTempR0.SetAt(0, 1);

        iTempR1 <<= 1;

        if (iTempR0.GetAt(127)) {
            iTempR0 += iTempR2;
        } else {
            iTempR1.SetAt(0, 1);
            iTempR0 -= iTempR2;
        }
    }

    iTempR1 <<= 1;

    if (!iTempR0.GetAt(127)) {
        iTempR1.SetAt(0, 1);
    } else
        iTempR0 += iTempR2;

    if (bDivrNegative ^ bDivdNegative) {
        iTempR1.Complement();
    }

    iQuotient = iTempR1;
    iRemainder = iTempR0;
}

// Set or Clear one bit where you want
void CHSInt128::SetAt(int uIndex, bool bSet) {
    int dwBitAt = (0X00000001 << (uIndex % 32));

    if (bSet) {
        if (uIndex < 32)
            m_A |= dwBitAt;
        else if (uIndex < 64)
            m_B |= dwBitAt;
        else if (uIndex < 96)
            m_C |= dwBitAt;
        else
            m_D |= dwBitAt;
    } else {
        if (uIndex < 32)
            m_A &= ~dwBitAt;
        else if (uIndex < 64)
            m_B &= ~dwBitAt;
        else if (uIndex < 96)
            m_C &= ~dwBitAt;
        else
            m_D &= ~dwBitAt;
    }
}

// Get Bit At ...
bool CHSInt128::GetAt(int uIndex) const {
    int dwBitAt = (0X00000001 << (uIndex % 32));

    if (uIndex < 32)
        return ((m_A & dwBitAt) != 0);
    else if (uIndex < 64)
        return ((m_B & dwBitAt) != 0);
    else if (uIndex < 96)
        return ((m_C & dwBitAt) != 0);
    else
        return ((m_D & dwBitAt) != 0);
}

// Is Me Zero ?
bool CHSInt128::IsZero() const {
    return (m_D == 0 &&
            m_C == 0 &&
            m_B == 0 &&
            m_A == 0);
}

// Set Me Zero
void CHSInt128::Zero() {
    m_A = m_B = m_C = m_D = 0;
}

// Get CHSInt128 Left
CHSInt128 CHSInt128::GetLeft(int uCount) const {
    CHSInt128 iTemp(*this);

    iTemp >>= (128 - uCount);

    return iTemp;
}

// Get Right uCount bit
CHSInt128 CHSInt128::GetRight(int uCount) const {
    CHSInt128 iTemp(*this);

    iTemp <<= (128 - uCount);
    iTemp >>= (128 - uCount);

    return iTemp;
}
