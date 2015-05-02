#include <stdio.h>
#include <Python.h>

#include <string>
#include "pythonImporter.h"

int callPythonFunction(char* fileName, char* funcName, char* argument){

	PyObject *pythonFileName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;
	
	// Initializes Python
	Py_Initialize();
	PySys_SetPath("~"); //relative path
	PyImport_ImportModule("pygame");


	PySys_SetPath(""); //relative path
	pythonFileName = PyString_FromString(fileName);
	pModule = PyImport_Import(pythonFileName);
	Py_DECREF(pythonFileName);
	
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, funcName);
		
		if (pFunc && PyCallable_Check(pFunc)) 
		{
			// Only if we need to pass in args
			pArgs = PyTuple_New(1);

			pValue = PyString_FromString(argument);
			if (!pValue) 
			{
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				fprintf(stderr, "Cannot convert argument!\n");
				return 1;
			}
			/* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);

			pValue = PyObject_CallObject(pFunc, pArgs);

			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				printf("Result of call :%ld\n", PyInt_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else
			{

				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 1;
			}
		}
		
		else 
		{
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argument);	
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	
	else
	{
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", funcName);
		return 1;
	}
	Py_Finalize();
	return 0;
	
}
