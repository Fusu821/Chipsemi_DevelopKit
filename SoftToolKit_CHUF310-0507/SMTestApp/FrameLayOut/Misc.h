#pragma once
class CommantLine
{
public:
	void ParseCommandLine( tstring& strCommandLine )
	{
		int iStart = 0, index = 0, iEnd = 0;
		int argc = 0;

		iStart = strCommandLine.find( 0x2D , 0);
		while ( (iStart  >= 0) && (iStart < (int)strCommandLine.length())  )
		{
			iEnd = strCommandLine.find( _T(" ") , iStart + 1);
			if( iEnd <= 0 ) iEnd = strCommandLine.length();
			tstring strTemp = strCommandLine.substr( iStart, iEnd - iStart );
			m_vecCommand[index++] = strTemp;
			iStart = strCommandLine.find( 0x2D , iStart + 1);
		}
	}
	bool HaveCommnd( const tstring& strCommand )
	{
		for ( int index = 0; index < MAX_PATH; ++index )
		{
			if( 0 == strCommand.compare( m_vecCommand[index] ) ) return true;
		}
		return false;
	}
private:
	tstring m_vecCommand[MAX_PATH];
} stuCommandLine;