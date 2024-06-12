import timeit, functools, os, pytest
from pydatastructs.trees.binary_trees import (RedBlackTree)
from pydatastructs.utils.misc_util import Backend

@pytest.mark.xfail
def test_cpp_RedBlackTree(**kwargs):
    cpp = Backend.CPP
    repeat = 1
    number = 1

    size = int(os.environ.get("PYDATASTRUCTS_BENCHMARK_SIZE", "1000"))
    size = kwargs.get("size", size)

    RBT = RedBlackTree
    b1 = RBT(backend=Backend.PYTHON)
    b2 = RBT(backend=Backend.CPP)

    def f(backend, tree):
        for node in range(-100000,100000):
            tree.insert(node, node)

    def g(backend, tree):
        for node in range(-100000, 100000):
            tree.search(node)
    def h(backend, tree):
        for node in range(-100000, 100000):
            tree.delete(node)


    kwds_dict_CPP = {"backend": Backend.CPP, "tree":b2}


    timer_cpp = timeit.Timer(functools.partial(f, **kwds_dict_CPP))
    cpp_insert = min(timer_cpp.repeat(repeat, number))

    print(timer_cpp)

    timer_cpp = timeit.Timer(functools.partial(g, **kwds_dict_CPP))
    cpp_search = min(timer_cpp.repeat(repeat, number))

    print(cpp_search)


    timer_cpp = timeit.Timer(functools.partial(h, **kwds_dict_CPP))
    cpp_delete = min(timer_cpp.repeat(repeat, number))

    print(cpp_delete)

test_cpp_RedBlackTree()
