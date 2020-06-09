// This file implements the IDebugDocumentInfo Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"

#include "PyIDebugDocumentInfo.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIDebugDocumentInfo::PyIDebugDocumentInfo(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIDebugDocumentInfo::~PyIDebugDocumentInfo() {}

/* static */ IDebugDocumentInfo *PyIDebugDocumentInfo::GetI(PyObject *self)
{
    return (IDebugDocumentInfo *)PyIUnknown::GetI(self);
}

// @pymethod |PyIDebugDocumentInfo|GetName|Returns the specified name for the document.
PyObject *PyIDebugDocumentInfo::GetName(PyObject *self, PyObject *args)
{
    IDebugDocumentInfo *pIDDP = GetI(self);
    if (pIDDP == NULL)
        return NULL;
    DOCUMENTNAMETYPE dnt;
    if (!PyArg_ParseTuple(args, "i:GetName", &dnt))
        return NULL;
    BSTR pbstrName;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIDDP->GetName(dnt, &pbstrName);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);

    PyObject *obpbstrName = MakeBstrToObj(pbstrName);
    PyObject *pyretval = Py_BuildValue("O", obpbstrName);
    Py_XDECREF(obpbstrName);
    SysFreeString(pbstrName);
    return pyretval;
}

// @pymethod <o PyIID>|PyIDebugDocumentInfo|GetDocumentClassId|Returns a CLSID describing the document type.
PyObject *PyIDebugDocumentInfo::GetDocumentClassId(PyObject *self, PyObject *args)
{
    IDebugDocumentInfo *pIDD = GetI(self);
    if (pIDD == NULL)
        return NULL;
    if (!PyArg_ParseTuple(args, ":GetDocumentClassId"))
        return NULL;
    CLSID pclsidDocument;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIDD->GetDocumentClassId(&pclsidDocument);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return SetPythonCOMError(self, hr);

    PyObject *obpclsidDocument = PyWinObject_FromIID(pclsidDocument);
    PyObject *pyretval = Py_BuildValue("O", obpclsidDocument);
    Py_XDECREF(obpclsidDocument);
    return pyretval;
}

// @object PyIDebugDocumentInfo|Provides information on a document, which may or may not be instantiated.
static struct PyMethodDef PyIDebugDocumentInfo_methods[] = {
    {"GetName", PyIDebugDocumentInfo::GetName, 1},  // @pymeth GetName|Returns the specified name for the document.
    {"GetDocumentClassId", PyIDebugDocumentInfo::GetDocumentClassId,
     1},  // @pymeth GetDocumentClassId|Returns a CLSID describing the document type.
    {NULL}};

PyComTypeObject PyIDebugDocumentInfo::type("PyIDebugDocumentInfo", &PyIUnknown::type, sizeof(PyIDebugDocumentInfo),
                                           PyIDebugDocumentInfo_methods, GET_PYCOM_CTOR(PyIDebugDocumentInfo));
// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGDebugDocumentInfo::GetName(
    /* [in]  */ DOCUMENTNAMETYPE dnt,
    /* [out] */ BSTR __RPC_FAR *pbstrName)

{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetName", &result, "i", dnt);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obpbstrName;
    if (!PyArg_Parse(result, "O", &obpbstrName))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyCom_BstrFromPyObject(obpbstrName, pbstrName))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGDebugDocumentInfo::GetDocumentClassId(
    /* [out] */ GUID __RPC_FAR *pclsidDocument)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("GetDocumentClassId", &result);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obpclsidDocument;
    if (!PyArg_Parse(result, "O", &obpclsidDocument))
        return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    BOOL bPythonIsHappy = TRUE;
    if (!PyWinObject_AsIID(obpclsidDocument, pclsidDocument))
        bPythonIsHappy = FALSE;
    if (!bPythonIsHappy)
        hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
    Py_DECREF(result);
    return hr;
}