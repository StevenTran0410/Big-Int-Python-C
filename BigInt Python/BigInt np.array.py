import numpy as np
import random
import multiprocessing as mp
import time


def remove_leading(string: str, c: str) -> str:  # Can use string.lstrip('0')
    count = 0
    for i in string:
        if (i != c):
            return string[count:len(string)]
        count += 1
    return ''


def abs_sub(first, second):  # Absolute subtraction
    if first > second:
        return first - second
    else:
        return second - first


class UintN:
    test_base = [2, 3, 5, 7, 11, 13, 17, 19, 23,
                 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]

    BigInt = np.empty(0, dtype=int)

    def __init__(self, number=0) -> list:
        if number == 0:
            self.BigInt = np.append(self.BigInt, 0)
        else:
            if isinstance(number, int):  # Int constructor
                while number:
                    self.BigInt = np.append(self.BigInt, number % 10)
                    number = int(number / 10)

            if isinstance(number, str):  # String constructor
                temp = remove_leading(number, '0')
                if len(temp) == 0:
                    temp = '0'
                for i in range(len(temp), 0, -1):
                    if not temp[i - 1].isdigit():  # If detect not number raise Exception
                        raise Exception("Not a valid number")
                    self.BigInt = np.append(self.BigInt, int(temp[i-1]))

            if isinstance(number, UintN):       # UintN constructor
                self.BigInt = number.BigInt

        self.BigInt = np.int8(self.BigInt)

    def print(self):
        for i in range(len(self.BigInt) - 1, -1, -1):
            print(self.BigInt[i], end='')
        print("\n")

    def size(self):
        return np.size(self.BigInt)

    def Null(self) -> bool:
        if self.size() == 1 and self.BigInt[0] == 0:
            return True
        return False

    def __lt__(self, second) -> bool:
        if not isinstance(second, UintN):
            second = UintN(second)

        n = self.size()
        m = second.size()
        # If not equal length than compare then length
        if n != m:
            return n < m
        # if equal length than compare each digit untill find out which pair is differn than comparision
        for i in range(n-1, -1, -1):
            if self.BigInt[i] != second.BigInt[i]:
                return self.BigInt[i] < second.BigInt[i]
        return False

    def __gt__(self, second) -> bool:
        if not isinstance(second, UintN):
            second = UintN(second)
        return second < self

    def __ge__(self, second) -> bool:
        return not self < second

    def __le__(self, second) -> bool:
        return not self > second

    def __eq__(self, second) -> bool:
        if not isinstance(second, UintN):
            second = UintN(second)
        return np.array_equal(self.BigInt, second.BigInt)
        # m = self.size()
        # n = second.size()
        # if m != n:
        #     return False
        # else:
        #     for i in range(n):
        #         if self.BigInt[i] != second.BigInt[i]:
        #             return False
        # return True

    def __ne__(self, second) -> bool:
        if not isinstance(second, UintN):
            second = UintN(second)
        return not self == second

    def __add__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)
        temp = self
        temp += second
        return temp

    def __iadd__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)

        t = int(0)
        n = self.size()
        m = second.size()
        temp = UintN()

        if m > n:
            temp = np.uint8(np.zeros(m - n, dtype=int))
            self.BigInt = np.concatenate((self.BigInt, temp))
        n = self.size()

        for i in range(n):
            # Doing addition math like we normal do
            if i < m:
                s = self.BigInt[i] + second.BigInt[i] + t
            else:
                s = self.BigInt[i] + t
            t = int(s/10)
            temp.BigInt = np.append(temp.BigInt, s % 10)
        temp.BigInt = temp.BigInt[1:]  # Remove 0 infront

        if t:
            temp.BigInt = np.append(temp.BigInt, t)
        self = temp
        return self

    def __sub__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)
        temp = self
        temp -= second
        return temp

    def __isub__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)

        t = int(0)
        n = self.size()
        m = second.size()
        temp = UintN()

        for i in range(n):
            # Do subtraction like we normal do \
            if i < m:
                s = self.BigInt[i] - second.BigInt[i] + t
            else:
                s = self.BigInt[i] + t

            if s < 0:
                s += 10
                t = -1
            else:
                t = 0
            temp.BigInt = np.append(temp.BigInt, s)
        temp.BigInt = temp.BigInt[1:]   # Remove zeros infront

        # Also remove zeros infront
        while n > 1 and temp.BigInt[n-1] == 0:
            temp.BigInt = temp.BigInt[:n-1]
            n -= 1
        self = temp
        return self

    def __mul__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)
        temp = self
        temp *= second
        return temp

    def __imul__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)

        if self.Null() or second.Null():
            self = UintN()
            return self

        n = self.size()
        m = second.size()
        temp = UintN()
        temp.BigInt = temp.BigInt[1:]
        v = np.zeros(n + m, int)
        # Multiply each digit and add it into an array
        for i in range(n):
            for j in range(m):
                v[i+j] += (self.BigInt[i] * second.BigInt[j])
        n += m
        t = 0
        # Take the last digit from each elements from array add it to the BigInt than
        # add the other digit to the next operation
        for i in range(n):
            s = t + v[i]
            v[i] = s % 10
            t = int(s/10)
            temp.BigInt = np.append(temp.BigInt, v[i])
        # Removes Zeros
        for i in range(n - 1, 0, -1):
            if not v[i]:
                temp.BigInt = temp.BigInt[0:i]
            else:
                break
        self = temp
        return self

    def __floordiv__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)
        temp = self
        temp //= second
        return temp

    def __ifloordiv__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)

        if self == second:
            self = UintN(1)
            return self

        if self < second:
            self = UintN()
            return self
        # Run Debug and you will understand how it work
        lgcat = int(0)
        n = self.size()
        temp = UintN()
        temp.BigInt = temp.BigInt[1:]
        cat = np.zeros(n, int)
        t = UintN()
        i = n - 1

        while t * 10 + int(self.BigInt[i]) < second:
            t *= 10
            t += int(self.BigInt[i])
            i -= 1
        while i >= 0:
            t = t * 10 + int(self.BigInt[i])
            cc = 9
            while UintN(cc) * second > t:
                cc -= 1
            t -= UintN(cc) * second
            cat[lgcat] = cc
            lgcat += 1
            i -= 1

        for j in range(lgcat):
            temp.BigInt = np.append(temp.BigInt, cat[lgcat - j - 1])
        self = temp
        self.BigInt = np.int8(self.BigInt)
        return self

    def __mod__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)
        temp = self
        temp %= second
        return temp

    def __imod__(self, second):
        if not isinstance(second, UintN):
            second = UintN(second)

        if self == second:
            self = UintN()
            return self

        if self < second:
            return self

        # Run Debug and you will understand how it work
        lgcat = int(0)
        n = self.size()
        cat = np.zeros(n, int)
        t = UintN()
        i = n - 1

        while t * 10 + int(self.BigInt[i]) < second:
            t *= 10
            t += int(self.BigInt[i])
            i -= 1

        while i >= 0:
            t = t * 10 + int(self.BigInt[i])
            cc = 9
            while UintN(cc) * second > t:
                cc -= 1
            t -= UintN(cc) * second
            cat[lgcat] = cc
            lgcat += 1
            i -= 1

        self = t
        self.BigInt = np.int8(self.BigInt)
        return self

    def __pow__(self, exponent):
        if not isinstance(exponent, UintN):
            exponent = UintN(exponent)
        temp = self
        temp **= exponent
        return temp

    def __ipow__(self, exponent):
        if exponent < 0:
            raise ValueError('Cannot raise an BigInteger to a negative power.')

        if self == 0:
            return self

        if not isinstance(exponent, UintN):
            exponent = UintN(exponent)

        res = UintN(1)

        while exponent > 0:
            if exponent % 2 == 1:
                res *= self

            exponent = exponent//2

            if exponent > 0:
                self *= self

        self = res
        return self

    def sqrt(self):
        res = self
        temp = UintN()
        a = abs_sub(res, temp)
        while a >= 1:
            temp = res
            res = (temp + (self//temp)) // 2
            a = abs_sub(res, temp)
        return res

    def ModularExponentiation(self, number, exponent, n):
        if exponent < 0:
            raise ValueError('Cannot raise an BigInteger to a negative power.')
        if n < 2:
            raise ValueError(
                'Cannot perform a modulo operation against a BigInteger less than 2')

        if number == 0:
            return number
        if number >= n:
            number %= n
        res = UintN(1)

        while exponent > 0:
            if exponent % 2 == 1:
                res = (res * number) % n
            exponent //= 2
            number = (number*number) % n

        return res

    def PrimeNumber_MillerRabinsImprove(self) -> bool:
        if self == 1 or self == 0 or self % 2 == 0:
            return False
        elif self <= 3:
            return True

        n = self.size()
        if n < 4:
            index = 1
        elif n < 13:
            index = int(n/2) - 1
        else:
            index = int(n/2)
            if index > 10:
                index = 5

        pool = mp.Pool(11)

        list_base = random.sample(self.test_base, index)

        d = self - 1
        comparision = self - 1
        num_exponent = 0

        while d % 2 == 0:
            num_exponent += 1
            d //= 2

        flag = True

        args_1 = []
        for i in range(index):
            args_1.append((UintN(list_base[i]), d, self))

        drones_1 = pool.starmap_async(self.ModularExponentiation, args_1)
        base_1 = drones_1.get()

        for i in range(index):
            if base_1[i] != 1 and base_1[i] != comparision:
                args_2 = []
                for r in range(1, num_exponent):
                    args_2.append((UintN(list_base[i]), UintN(2**r)*d, self))

                if len(args_2):
                    drones_2 = pool.starmap_async(
                        self.ModularExponentiation, args_2)
                    base_2 = drones_2.get()
                    for r in range(0, num_exponent - 1):
                        if base_2[r] != comparision and base_2[r] != 1:
                            flag = False
                        else:
                            flag = True
                            break
                    if not flag:
                        return flag
                else:
                    return False
        return flag


if __name__ == '__main__':
    e1 = UintN('485903650630522852040551973461')
    start = time.time()
    flag = e1.PrimeNumber_MillerRabinsImprove()
    end = time.time()
    print(end - start)
    if flag:
        print(True)
    else:
        print(False)
