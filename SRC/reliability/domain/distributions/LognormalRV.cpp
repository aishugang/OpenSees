/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 2001, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** Reliability module developed by:                                   **
**   Terje Haukaas (haukaas@ce.berkeley.edu)                          **
**   Armen Der Kiureghian (adk@ce.berkeley.edu)                       **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Revision: 1.3 $
// $Date: 2001-08-01 00:25:26 $
// $Source: /usr/local/cvs/OpenSees/SRC/reliability/domain/distributions/LognormalRV.cpp,v $


//
// Written by Terje Haukaas (haukaas@ce.berkeley.edu) during Spring 2000
// Revised: haukaas 06/00 (core code)
//			haukaas 06/01 (made part of official OpenSees)
//

#include <LognormalRV.h>
#include <NormalRV.h>
#include <math.h>
#include <string.h>

LognormalRV::LognormalRV(int passedTag, 
		 double passedMean,
		 double passedStdv,
		 double passedStartValue)
:RandomVariable(passedTag, passedMean, passedStdv, passedStartValue)
{
	type = new char[100];
	strcpy(type,"LOGNORMAL");
	tag = passedTag ;
	zeta = sqrt(   log(   1+(passedStdv/passedMean)*(passedStdv/passedMean)   )   );
	lambda = log(passedMean) - 0.5*zeta*zeta;
	startValue = passedStartValue;
}
LognormalRV::LognormalRV(int passedTag, 
		 double passedParameter1,
		 double passedParameter2,
		 double passedParameter3,
		 double passedParameter4,
		 double passedStartValue)
:RandomVariable(passedTag, passedParameter1, passedParameter2, passedParameter3, passedParameter4, passedStartValue)
{
	type = new char[100];
	strcpy(type,"LOGNORMAL");
	tag = passedTag ;
	lambda = passedParameter1;
	zeta = passedParameter2;
	startValue = passedStartValue;
}
LognormalRV::LognormalRV(int passedTag, 
		 double passedMean,
		 double passedStdv)
:RandomVariable(passedTag, passedMean, passedStdv)
{
	type = new char[100];
	strcpy(type,"LOGNORMAL");
	tag = passedTag ;
	zeta = sqrt(   log(   1+(passedStdv/passedMean)*(passedStdv/passedMean)   )   );
	lambda = log(passedMean) - 0.5*zeta*zeta;
	startValue = getMean();
}
LognormalRV::LognormalRV(int passedTag, 
		 double passedParameter1,
		 double passedParameter2,
		 double passedParameter3,
		 double passedParameter4)
:RandomVariable(passedTag, passedParameter1, passedParameter2, passedParameter3, passedParameter4)
{
	type = new char[100];
	strcpy(type,"LOGNORMAL");
	tag = passedTag ;
	lambda = passedParameter1;
	zeta = passedParameter2;
	startValue = getMean();
}


LognormalRV::~LognormalRV()
{
  if (type != 0)
    delete [] type;
}


void
LognormalRV::Print(ostream &s, int flag)
{
}


double
LognormalRV::getPDFvalue(double rvValue)
{
	double result;
	if ( 0.0 < rvValue ) {
		double pi = 3.14159265358979;
		result = 1/(sqrt(2*pi)*zeta*rvValue) * exp(-0.5* pow ( (log(rvValue)-lambda) / zeta, 2 )  );
	}
	else {
		result = 0.0;
	}
	return result;
}


double
LognormalRV::getCDFvalue(double rvValue)
{
	double result;
	if ( 0.0 < rvValue ) {
		RandomVariable *aStandardNormalRV;
		aStandardNormalRV= new NormalRV( 1, 0.0, 1.0, 0.0);
		result = aStandardNormalRV->getCDFvalue((log(rvValue)-lambda)/zeta);
		delete aStandardNormalRV;	
	}
	else {
		result = 0.0;
	}
	return result;
}


double
LognormalRV::getInverseCDFvalue(double probValue)
{
	if ( probValue > 1.0 || probValue < 0.0) {
		cerr << "Invalid probability value input to inverse CDF function" << endl;
		return 0.0;
	}
	else {
		RandomVariable *aStandardNormalRV;
		aStandardNormalRV= new NormalRV( 1, 0.0, 1.0, 0.0);
		double inverseNormal = aStandardNormalRV->getInverseCDFvalue(probValue);
		delete aStandardNormalRV;	
		return exp(getStdv() * inverseNormal + getMean());
	}
}


char *
LognormalRV::getType()
{
	return type;
}


double 
LognormalRV::getMean()
{
	return exp(lambda+0.5*zeta*zeta);
}



double 
LognormalRV::getStdv()
{
	return exp(lambda+0.5*zeta*zeta)*sqrt(exp(zeta*zeta)-1);
}


double 
LognormalRV::getStartValue()
{
	return startValue;
}


double LognormalRV::getParameter1()  {return lambda;}
double LognormalRV::getParameter2()  {return zeta;}
double LognormalRV::getParameter3()  {cerr<<"No such parameter in r.v. #"<<tag<<endl; return 0.0;}
double LognormalRV::getParameter4()  {cerr<<"No such parameter in r.v. #"<<tag<<endl; return 0.0;}
