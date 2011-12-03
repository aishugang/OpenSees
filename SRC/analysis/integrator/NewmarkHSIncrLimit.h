/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
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
** ****************************************************************** */

// $Revision: $
// $Date: $
// $Source: $

#ifndef NewmarkHSIncrLimit_h
#define NewmarkHSIncrLimit_h

// Written: Andreas Schellenberg (andreas.schellenberg@gmx.net)
// Created: 11/09
// Revision: A
//
// Description: This file contains the class definition for NewmarkHSIncrLimit.
// NewmarkHSIncrLimit is an algorithmic class for performing a transient analysis
// using the Newmark integration scheme. This is a special integrator for hybrid
// simulation where the response increments are limited by a user specified value.
// This enhances the smoothness of the convergence path and reduces the
// possibility of spurious loading/unloading cycles during iteration.
//
// What: "@(#) NewmarkHSIncrLimit.h, revA"

#include <TransientIntegrator.h>

class DOF_Group;
class FE_Element;
class Vector;

class NewmarkHSIncrLimit : public TransientIntegrator
{
public:
    // constructors
    NewmarkHSIncrLimit();
    NewmarkHSIncrLimit(double gamma, double beta, double limit,
        int normType);
    NewmarkHSIncrLimit(double gamma, double beta, double limit,
        int normType,
        double alphaM, double betaK, double betaKi, double betaKc);
    
    // destructor
    ~NewmarkHSIncrLimit();
    
    // methods which define what the FE_Element and DOF_Groups add
    // to the system of equation object.
    int formEleTangent(FE_Element *theEle);
    int formNodTangent(DOF_Group *theDof);
    
    int domainChanged(void);    
    int newStep(double deltaT);    
    int revertToLastStep(void);        
    int update(const Vector &deltaU);
    
    virtual int sendSelf(int commitTag, Channel &theChannel);
    virtual int recvSelf(int commitTag, Channel &theChannel, FEM_ObjectBroker &theBroker);
    
    void Print(OPS_Stream &s, int flag = 0);        
        
private:
    double gamma;
    double beta;
    double limit;   // disp increment limit
    int normType;   // type of norm that is used to limit increments
    
    // rayleigh damping factors
    double alphaM;
    double betaK;
    double betaKi;
    double betaKc;
    
    double c1, c2, c3;              // some constants we need to keep
    Vector *Ut, *Utdot, *Utdotdot;  // response quantities at time t
    Vector *U, *Udot, *Udotdot;     // response quantities at time t+deltaT    
    Vector *scaledDeltaU;           // scaled displacement increment
};

#endif