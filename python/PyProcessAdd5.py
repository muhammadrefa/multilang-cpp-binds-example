from mylib.NumberProcessor import NumberProcessorProxy


class PyProcessAdd5(NumberProcessorProxy):
    def __init__(self, **kwargs):
        super().__init__()

    def process(self):
        number = super().get_number()
        number += 5
        super().set_number(number)

    def print_number(self):
        print(f"Python", end=" ")
        super().print_number()
