#ifndef TREES_SELFBALANCINGSelfBalancingBinaryTree_HPP
#define TREES_SELFBALANCINGSelfBalancingBinaryTree_HPP

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>
#include <cstdlib>
#include "../../../utils/_backend/cpp/utils.hpp"
#include "../../../utils/_backend/cpp/TreeNode.hpp"
#include "../../../linear_data_structures/_backend/cpp/arrays/ArrayForTrees.hpp"
#include "../../../linear_data_structures/_backend/cpp/arrays/DynamicOneDimensionalArray.hpp"
#include "BinarySearchTree.hpp"

typedef struct {
    PyObject_HEAD
    BinarySearchTree* bst;
} SelfBalancingBinaryTree;

static void SelfBalancingBinaryTree_dealloc(SelfBalancingBinaryTree *self) {
    Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}

static PyObject* SelfBalancingBinaryTree___new__(PyTypeObject* type, PyObject *args, PyObject *kwds) {
    SelfBalancingBinaryTree *self;
    self = reinterpret_cast<SelfBalancingBinaryTree*>(type->tp_alloc(type, 0));

    if (PyType_Ready(&BinarySearchTreeType) < 0) { // This has to be present to finalize a type object. This should be called on all type objects to finish their initialization.
        return NULL;
    }
    PyObject* p = BinarySearchTree___new__(&BinarySearchTreeType, args, kwds);
    self->bst = reinterpret_cast<BinarySearchTree*>(p);

    return reinterpret_cast<PyObject*>(self);
}

static PyObject* SelfBalancingBinaryTree___str__(SelfBalancingBinaryTree *self) {
    return BinarySearchTree___str__(self->bst);
}

static PyObject* SelfBalancingBinaryTree_insert(SelfBalancingBinaryTree* self, PyObject* args) {
    return BinarySearchTree_insert(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree_search(SelfBalancingBinaryTree* self, PyObject *args, PyObject *kwds) {
    return BinarySearchTree_search(self->bst, args, kwds);
}

static PyObject* SelfBalancingBinaryTree_delete(SelfBalancingBinaryTree* self, PyObject *args, PyObject *kwds) {
    return BinarySearchTree_delete(self->bst, args, kwds);
}

static PyObject* SelfBalancingBinaryTree_lower_bound(SelfBalancingBinaryTree* self, PyObject *args, PyObject *kwds) {
    return BinarySearchTree_lower_bound(self->bst, args, kwds);
}

static PyObject* SelfBalancingBinaryTree_upper_bound(SelfBalancingBinaryTree* self, PyObject *args, PyObject *kwds) {
    return BinarySearchTree_upper_bound(self->bst, args, kwds);
}

static PyObject* SelfBalancingBinaryTree__simple_path(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree__simple_path(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree__lca_1(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree__simple_path(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree__lca_2(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree__simple_path(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree_lowest_common_ancestor(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree_lowest_common_ancestor(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree_rank(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree_rank(self->bst, args);
}

static PyObject* SelfBalancingBinaryTree_select(SelfBalancingBinaryTree* self, PyObject *args) {
    return BinarySearchTree_select(self->bst, args);
}

static struct PyMethodDef SelfBalancingBinaryTree_PyMethodDef[] = {
    {"insert", (PyCFunction) SelfBalancingBinaryTree_insert, METH_VARARGS | METH_KEYWORDS, NULL},
    {"delete", (PyCFunction) SelfBalancingBinaryTree_delete, METH_VARARGS | METH_KEYWORDS, NULL},
    {"search", (PyCFunction) SelfBalancingBinaryTree_search, METH_VARARGS | METH_KEYWORDS, NULL},
    {"lower_bound", (PyCFunction) SelfBalancingBinaryTree_lower_bound, METH_VARARGS | METH_KEYWORDS, NULL},
    {"upper_bound", (PyCFunction) SelfBalancingBinaryTree_upper_bound, METH_VARARGS | METH_KEYWORDS, NULL},
    {"_simple_path", (PyCFunction) SelfBalancingBinaryTree__simple_path, METH_VARARGS, NULL},
    {"_lca_1", (PyCFunction) SelfBalancingBinaryTree__lca_1, METH_VARARGS, NULL},
    {"_lca_2", (PyCFunction) SelfBalancingBinaryTree__lca_2, METH_VARARGS, NULL},
    {"lowest_common_ancestor", (PyCFunction) SelfBalancingBinaryTree_lowest_common_ancestor, METH_VARARGS, NULL},
    {"rank", (PyCFunction) SelfBalancingBinaryTree_rank, METH_VARARGS, NULL},
    {"select", (PyCFunction) SelfBalancingBinaryTree_select, METH_VARARGS, NULL},
    {NULL}
};

static PyMemberDef SelfBalancingBinaryTree_PyMemberDef[] = {
    {NULL}  /* Sentinel */
};


static PyTypeObject SelfBalancingBinaryTreeType = {
    /* tp_name */ PyVarObject_HEAD_INIT(NULL, 0) "SelfBalancingBinaryTree",
    /* tp_basicsize */ sizeof(SelfBalancingBinaryTree),
    /* tp_itemsize */ 0,
    /* tp_dealloc */ (destructor) SelfBalancingBinaryTree_dealloc,
    /* tp_print */ 0,
    /* tp_getattr */ 0,
    /* tp_setattr */ 0,
    /* tp_reserved */ 0,
    /* tp_repr */ 0,
    /* tp_as_number */ 0,
    /* tp_as_sequence */ 0,
    /* tp_as_mapping */ 0,
    /* tp_hash  */ 0,
    /* tp_call */ 0,
    /* tp_str */ (reprfunc) SelfBalancingBinaryTree___str__,
    /* tp_getattro */ 0,
    /* tp_setattro */ 0,
    /* tp_as_buffer */ 0,
    /* tp_flags */ Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    /* tp_doc */ 0,
    /* tp_traverse */ 0,
    /* tp_clear */ 0,
    /* tp_richcompare */ 0,
    /* tp_weaklistoffset */ 0,
    /* tp_iter */ 0,
    /* tp_iternext */ 0,
    /* tp_methods */ SelfBalancingBinaryTree_PyMethodDef,
    /* tp_members */ SelfBalancingBinaryTree_PyMemberDef,
    /* tp_getset */ 0,
    /* tp_base */ &BinarySearchTreeType,
    /* tp_dict */ 0,
    /* tp_descr_get */ 0,
    /* tp_descr_set */ 0,
    /* tp_dictoffset */ 0,
    /* tp_init */ 0,
    /* tp_alloc */ 0,
    /* tp_new */ SelfBalancingBinaryTree___new__,
};

#endif