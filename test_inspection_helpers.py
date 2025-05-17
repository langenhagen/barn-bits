from c1.util.inspection_helpers import get_function_arguments, get_function_name


def some_free_function():
    return get_function_name()


def some_function_with_parameters(param1, param2=42, *myargs, **mykwargs):
    return get_function_arguments()


class TestClass:
    def some_method(self):
        return get_function_name()

    @staticmethod
    def some_static_method():
        return get_function_name()

    def some_method_with_parameters(self, param1, param2=42, *myargs, **mykwargs):
        return get_function_arguments()


class TestChildClass(TestClass):
    pass


class OtherTestChildClass(TestClass):
    def some_method(self) -> None:
        print("Hello from a derived method E.foo()")
        print(get_function_name())


def test_get_correct_free_function_name() -> None:
    assert some_free_function() == "some_free_function"


def test_get_correct_method_name() -> None:
    obj = TestClass()
    assert obj.some_method() == "some_method"


def test_get_correct_staticmethod_name() -> None:
    assert TestClass.some_static_method() == "some_static_method"


def test_get_correct_derived_method_name() -> None:
    obj = TestChildClass()
    assert obj.some_method() == "some_method"


def test_get_correct_derived_staticmethod_name() -> None:
    assert TestClass.some_static_method() == "some_static_method"


def test_get_correct_overridden_method_name() -> None:
    obj = TestChildClass()
    assert obj.some_method() == "some_method"


def test_get_correct_function_arguments():
    assert 0 == cmp(
        some_function_with_parameters(1),
        {'param1': 1, 'param2': 42, 'myargs': (), 'mykwargs': {}}
    )
    assert 0 == cmp(
        some_function_with_parameters(22, 33, 'one', 'two'),
        {'param1': 22, 'param2': 33, 'myargs': ('one', 'two'), 'mykwargs': {}}
    )
    assert 0 == cmp(
        some_function_with_parameters(22, 33, 'three', foo=4),
        {'param1': 22, 'param2': 33, 'myargs': ('three',), 'mykwargs': {'foo': 4}}
    )


def test_get_correct_method_arguments():
    obj = TestClass()
    assert 0 == cmp(
        obj.some_method_with_parameters(1),
        {'param1': 1, 'param2': 42, 'myargs': (), 'mykwargs': {}}
    )
    assert 0 == cmp(
        obj.some_method_with_parameters(22, 33, 'one', 'two'),
        {'param1': 22, 'param2': 33, 'myargs': ('one', 'two'), 'mykwargs': {}}
    )
    assert 0 == cmp(
        obj.some_method_with_parameters(22, 33, 'three', foo=4),
        {'param1': 22, 'param2': 33, 'myargs': ('three',), 'mykwargs': {'foo': 4}}
    )
