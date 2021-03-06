/*
 *  KikiPyAction.cpp
 *  kiki
 */

#include "KikiPyAction.h"
#include "KikiEvent.h"

#include <KConsole.h>

// --------------------------------------------------------------------------------------------------------
KikiPyAction::KikiPyAction ( PyObject * self, PyObject * object, const std::string & name, int duration, int mode )
    : KikiAction (NULL, 0, name, duration, mode)
{
    python_self   = self;
    python_object = object;
    Py_INCREF(python_object);
}

// --------------------------------------------------------------------------------------------------------
KikiPyAction::~KikiPyAction ()
{
    Py_DECREF(python_object); 
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::init ()
{ 
    Py_INCREF(python_self);
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::perform ()
{
    PyObject * result = NULL;
    if (PyFunction_Check(python_object))
    {
        result = PyObject_CallFunctionObjArgs (python_object, NULL);
    }
    else if (PyMethod_Check(python_object))
    {
        result = PyObject_CallFunctionObjArgs (PyMethod_Function(python_object), 
                                               PyMethod_Self(python_object), NULL); 
    }
    else if (PyObject_HasAttrString(python_object, "performAction"))
    {
        result = PyObject_CallMethod (python_object,  const_cast<char*>("performAction"), 
                                                      const_cast<char*>("sf"), 
                                                      action_name.c_str(),
                                                      getRelativeTime());
    }
    if (result)
    {
        Py_DECREF(result);
    }
    else
    {
        KConsole::printError (kStringPrintf ("KikiPyAction::perform failed \"%s\"", action_name.c_str()));        
        PyErr_Print();
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::finish ()
{
    if (PyObject_HasAttrString(python_object, "finishAction"))
    {
      PyObject * result = PyObject_CallMethod(python_object, const_cast<char*>("finishAction"), const_cast<char*>("s"), action_name.c_str());
      if (result)
      {
        Py_DECREF(result);
      }
      else      
      {
          KConsole::printError("KikiPyAction::finish failed");
      }
    }
}

// --------------------------------------------------------------------------------------------------------
void KikiPyAction::finished ()
{ 
    if (PyObject_HasAttrString(python_object, "finishAction"))
    {
        PyObject * result = PyObject_CallMethod(python_object, const_cast<char*>("actionFinished"), const_cast<char*>("s"), action_name.c_str());
        if (result)
        {
          Py_DECREF(result);
        }
        else        
        {
            KConsole::printError("KikiPyAction::finished failed");
        }
    }
    reset();
   
    if (mode == KikiAction::ONCE)
    {
        Py_DECREF(python_self);
    }
}

