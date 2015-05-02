#include <stdio.h>
#include <Python.h>
#include <string>

//std::string test[10000];

int main(int argc, char *argv[]) {
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;
	
	if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }
	
	/*for (int i = 0; i < 10000; i++)
		test[i] = "average song name?;*/

	// Initializes Python
	Py_Initialize();
	PySys_SetPath("/home/mario/Documents/pythonTesting");
	pName = PyString_FromString(argv[1]);
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		
		if (pFunc && PyCallable_Check(pFunc)) 
		{
			// Only if we need to pass in args
			pArgs = PyTuple_New(argc - 3);
			for (i = 0; i < argc - 3; ++i) 
			{
				pValue = PyInt_FromLong(atoi(argv[i + 3]));
				if (!pValue) 
				{
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument!\n");
					return 1;
				}
				/* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
			}
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
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);	
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	
	else
	{
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}
	Py_Finalize();
	return 0;
	
}
