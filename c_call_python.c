#include <Python.h>

int func1(){
    Py_Initialize();
    PyRun_SimpleString("print('hello world in python and c')");
    Py_Finalize();
    return 0;
}

int func2()
{
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        return -1; //init python failed
    }
    PyObject *pmodule = PyImport_ImportModule("math"); 
    if (!pmodule)
    {
        printf("cannot find math module \n");
        return -1;
    }
    else
    {
        printf("PyImport_ImportModule success\n");
    }
 
    PyObject *pfunc = PyObject_GetAttrString(pmodule, "pow"); 
    if (!pfunc)
    {
        printf("cannot find pow\n");
        Py_XDECREF(pmodule);
        return -1;
    }
    else
    {
        printf("PyObject_GetAttrString success\n");
    }
    
    PyObject *pArgs = PyTuple_New(2);
    PyObject *pVal = Py_BuildValue("i", 3);     
    PyObject *pVal1 = Py_BuildValue("i", 5);
    PyTuple_SetItem(pArgs, 0, pVal);
    PyTuple_SetItem(pArgs, 1, pVal1);
    
    PyObject *pResult = PyObject_CallObject(pfunc, pArgs);
    int a;
    float b;
    PyArg_Parse(pResult, "i", &a);
    // PyArg_ParseTuple(pResult,"if",&a,&b);
    printf("%f\n", a);
 
    Py_XDECREF(pmodule);
    Py_XDECREF(pfunc);
    Py_XDECREF(pArgs);
    Py_XDECREF(pResult);
 
    Py_Finalize();
    
    return 0;
}

int func3()
{
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        return -1; //init python failed
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject *pmodule = PyImport_ImportModule("call_py"); 
    if (!pmodule)
    {
        printf("cannot find call_py.py\n");
        return -1;
    }
    else
    {
        printf("PyImport_ImportModule success\n");
    }
 
    PyObject *pfunc = PyObject_GetAttrString(pmodule, "func1"); 
    if (!pfunc)
    {
        printf("cannot find func\n");
        Py_XDECREF(pmodule);
        return -1;
    }
    else
    {
        printf("PyObject_GetAttrString success\n");
    }
    
    PyObject *pArgs = PyTuple_New(3);
    PyObject *pVender = Py_BuildValue("i", 2);     
    PyObject *pDataID = Py_BuildValue("i", 10001);
    PyObject *pyTupleList = PyTuple_New(2);        
    float arr_f[2];
    arr_f[0] = 78;
    arr_f[1] = 3.41;
    for (int i = 0; i < 2; i++)
    {
        PyTuple_SetItem(pyTupleList, i, Py_BuildValue("f", arr_f[i])); 
    }
 
    PyTuple_SetItem(pArgs, 0, pVender);
    PyTuple_SetItem(pArgs, 1, pDataID);
    PyTuple_SetItem(pArgs, 2, pyTupleList);
    
    PyObject *pResult = PyObject_CallObject(pfunc, pArgs);
    int a;
    float b;
    // PyArg_Parse(pResult, "i", &a);
    PyArg_ParseTuple(pResult,"if",&a,&b);
    printf("%d %f\n", a,b);
 
    Py_XDECREF(pmodule);
    Py_XDECREF(pfunc);
    Py_XDECREF(pArgs);
    Py_XDECREF(pResult);
 
    Py_Finalize();
    
    return 0;
}


int main(int argc, char *argv[]) {
    
    func1();
    func2();
    func3();

}

