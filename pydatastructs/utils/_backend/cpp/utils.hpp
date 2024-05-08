#ifndef UTILS_UTILS_HPP
#define UTILS_UTILS_HPP

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cstring>
#include <string>

PyObject *PyZero = PyLong_FromLong(0);
PyObject *PyOne = PyLong_FromLong(1);
PyObject *PyTwo = PyLong_FromLong(2);
const char* _encoding = "utf-8";
const char* _invalid_char = "<invalid-character>";

static char* PyObject_AsString(PyObject* obj) {
    return PyBytes_AS_STRING(PyUnicode_AsEncodedString(obj, _encoding, _invalid_char));
}

static PyObject* __str__(PyObject** array, size_t size, long last_pos_filled=-1) {
    std::string array___str__ = "[";
    size_t end = last_pos_filled == -1 ? size : (size_t) (last_pos_filled + 1);
    for( size_t i = 0; i < end; i++ ) {
        if( array[i] == Py_None ) {
            array___str__.append("''");
        } else {
            PyObject* array_i = PyObject_Str(array[i]);
            char* i___str__ = PyObject_AsString(array_i);
            array___str__.append("'" + std::string(i___str__) + "'");
        }
        if( i + 1 != end ) {
            array___str__.append(", ");
        }
    }
    array___str__.push_back(']');
    return PyUnicode_FromString(array___str__.c_str());
}

static int set_exception_if_dtype_mismatch(PyObject* value, PyObject* dtype) {
    if( !PyObject_IsInstance(value, dtype) ) {
        PyErr_WriteUnraisable(
            PyErr_Format(PyExc_TypeError,
            "Unable to store %s object in %s type array.",
            PyObject_AsString(PyObject_Repr(PyObject_Type(value))),
            PyObject_AsString(PyObject_Repr(dtype))));
        return 1;
    }
    return 0;
}

static int raise_exception_if_dtype_mismatch(PyObject* value, PyObject* dtype) {
    if( !PyObject_IsInstance(value, dtype) ) {
        PyErr_Format(PyExc_TypeError,
        "Unable to store %s object in %s type array.",
        PyObject_AsString(PyObject_Repr(PyObject_Type(value))),
        PyObject_AsString(PyObject_Repr(dtype)));
        return 1;
    }
    return 0;
}

static int raise_exception_if_not_array(PyObject* arg) {
    PyErr_Format(PyExc_TypeError,
        ("Unable to sort %s data structure. "
         "Only accepted types are OneDimensionalArray and DynamicOneDinesionalArray"),
        PyObject_AsString(PyObject_Repr(PyObject_Type(arg)))
    );
    return 1;
}

static int _check_type(PyObject* arg, PyTypeObject* type) {
    return strcmp(arg->ob_type->tp_name, type->tp_name) == 0;
}

static int _comp(PyObject* u, PyObject* v, PyObject* tcomp) {
    int u_isNone = u == Py_None;
    int v_isNone = v == Py_None;
    if( u_isNone && !v_isNone) {
        return 0;
    }
    if( !u_isNone && v_isNone ) {
        return 1;
    }
    if( u_isNone && v_isNone ) {
        return 0;
    }
    if( tcomp ) {
        PyObject* result_PyObject = PyObject_CallFunctionObjArgs(tcomp, u, v, NULL);
        if( !result_PyObject ) {
            PyErr_Format(PyExc_ValueError,
                "Unable to compare %s object with %s object.",
                PyObject_AsString(PyObject_Repr(PyObject_Type(u))),
                PyObject_AsString(PyObject_Repr(PyObject_Type(v)))
            );
        }
        return result_PyObject == Py_True;
    }

    int result = PyObject_RichCompareBool(u, v, Py_LE);
    if( result == -1 ) {
        PyErr_Format(PyExc_ValueError,
            "Unable to compare %s object with %s object.",
            PyObject_AsString(PyObject_Repr(PyObject_Type(u))),
            PyObject_AsString(PyObject_Repr(PyObject_Type(v)))
        );
    }
    return result;
}

// Binary Search Tree node
typedef struct {
    PyObject_HEAD
    int key;
    PyObject *data;
    int left;
    int right;
    int is_root;
    int height;
    int parent;
    int size;
} TreeNode;

static PyObject *Treenode___new__(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    TreeNode *self;
    self = (TreeNode *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->data = Py_None;
        self->left = -1;
        self->right = -1;
        self->is_root = 0;
        self->height = 0;
        self->parent = -1;
        self->size = 1;
        if (!PyArg_ParseTuple(args, "i|O", &self->key, &self->data)) {
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *)self;
}

static PyObject *
TreeNode_str(TreeNode *self) {
    return PyUnicode_FromFormat("(%d, %S, %d, %d)",
                                self->left, self->key, self->data, self->right);
}

static PyMethodDef TreeNode_methods[] = {
    {"__str__", (PyCFunction)TreeNode_str, METH_NOARGS, "Return string representation of the node."},
    {NULL}  /* Sentinel */
};

static PyTypeObject TreeNodeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "treenode.TreeNode",
    .tp_doc = "TreeNode objects",
    .tp_basicsize = sizeof(TreeNode),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = Treenode___new__,
    .tp_str = (reprfunc)TreeNode_str,
    .tp_methods = TreeNode_methods,
};

static struct PyModuleDef treenode_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "treenode",
    .m_doc = "Module that provides TreeNode class",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_treenode(void) {
    PyObject *m;
    if (PyType_Ready(&TreeNodeType) < 0)
        return NULL;
    m = PyModule_Create(&treenode_module);
    if (m == NULL)
        return NULL;
    Py_INCREF(&TreeNodeType);
    PyModule_AddObject(m, "TreeNode", (PyObject *)&TreeNodeType);
    return m;
}

#endif
