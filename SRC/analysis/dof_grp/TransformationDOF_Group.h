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
                                                                        
// $Revision: 1.3 $
// $Date: 2004-10-12 21:52:25 $
// $Source: /usr/local/cvs/OpenSees/SRC/analysis/dof_grp/TransformationDOF_Group.h,v $
                                                                        
                                                                        
#ifndef TransformationDOF_Group_h
#define TransformationDOF_Group_h

// File: ~/analysis/dof_grp/TransformationDOF_Group.h
// 
// Written: fmk 
// Created: 05/99
// Revision: A
//
// Description: This file contains the class definition for 
// TransformationDOF_Group. A TransformationDOF_Group object is 
// instantiated by the TransformationConstraintHandler for 
// every node in the domain which is constrained by an MP_Constraint
// or an SP_Constrant.
//
// What: "@(#) TransformationDOF_Group.h, revA"

#include <DOF_Group.h>

class MP_Constraint;
class SP_Constraint;

class TransformationDOF_Group: public DOF_Group
{
  public:
    TransformationDOF_Group(int tag, Node *myNode, MP_Constraint *mp);
    TransformationDOF_Group(int tag, Node *myNode);    
    ~TransformationDOF_Group();    
    
    // methods dealing with the ID and transformation matrix
    int doneID(void);    
    const ID &getID(void) const; 
    virtual void setID(int dof, int value);    
    Matrix *getT(void);
    virtual int getNumDOF(void) const;    
    virtual int getNumFreeDOF(void) const;
    virtual int getNumConstrainedDOF(void) const;
    
    // methods to form the tangent
    const Matrix &getTangent(Integrator *theIntegrator);

    // methods to form the unbalance
    const Vector &getUnbalance(Integrator *theIntegrator);
    virtual void  addM_Force(const Vector &Udotdot, double fact = 1.0);        

    virtual const Vector &getTangForce(const Vector &x, double fact = 1.0);
    virtual const Vector &getC_Force(const Vector &x, double fact = 1.0);
    virtual const Vector &getM_Force(const Vector &x, double fact = 1.0);
    
    // methods to obtain committed responses from the nodes
    const Vector & getCommittedDisp(void);
    const Vector & getCommittedVel(void);
    const Vector & getCommittedAccel(void);
    
    // methods to update the trial response at the nodes
    void setNodeDisp(const Vector &u);
    void setNodeVel(const Vector &udot);
    void setNodeAccel(const Vector &udotdot);

    void incrNodeDisp(const Vector &u);
    void incrNodeVel(const Vector &udot);
    void incrNodeAccel(const Vector &udotdot);

    virtual void setEigenvector(int mode, const Vector &eigenvalue);

    int addSP_Constraint(SP_Constraint &theSP);
    int enforceSPs(void);
    
  protected:
    
  private:
    // private variables - a copy for each object of the class            
    MP_Constraint *theMP;
    Matrix *Trans;
    Matrix *modTangent;
    Vector *modUnbalance;
    ID *modID;
    int modNumDOF;
    
    SP_Constraint **theSPs;
    
    // static variables - single copy for all objects of the class	    
    static Matrix **modMatrices; // array of pointers to class wide matrices
    static Vector **modVectors;  // array of pointers to class widde vectors
    static int numTransDOFs;           // number of objects        
};

#endif

