class Hashtable:
    def __init__(self):
        self.m = int(input("Enter size of hash table: "))
        self.hashTable = [None] * self.m
        self.elecount = 0

    def hashFunction(self, key):
        return key % self.m

    def isFull(self):
        return self.elecount == self.m

    def linearProbe(self, key, data):
        index = self.hashFunction(key)
        while self.hashTable[index] is not None:
            index = (index + 1) % self.m
        self.hashTable[index] = [key, data]
        self.elecount += 1

    def quadraticProbe(self, key, data):
        index, i = self.hashFunction(key), 0
        while self.hashTable[index] is not None:
            i += 1
            index = (index + i * i) % self.m
        self.hashTable[index] = [key, data]
        self.elecount += 1

    def search(self, key, data, method="linear"):
        index, i = self.hashFunction(key), 0
        while self.hashTable[index] is not None:
            if self.hashTable[index] == [key, data]:
                return index
            i += 1
            index = (index + (i * i if method == "quadratic" else 1)) % self.m
        return None

    def insert(self, key, data, method="linear"):
        if self.isFull():
            print("Table is full")
            return
        index = self.hashFunction(key)
        if self.hashTable[index] is None:
            self.hashTable[index] = [key, data]
            self.elecount += 1
        else:
            print("Collision occurred, applying", method, "probing")
            (self.linearProbe if method == "linear" else self.quadraticProbe)(key, data)

def menu():
    obj = Hashtable()
    while True:
        print("\n1. Insert (Linear)\n2. Insert (Quadratic)\n3. Search\n4. Exit")
        choice = int(input("Enter choice: "))
        if choice == 4:
            break
        key = int(input("Enter key: "))
        data = input("Enter data: ")
        if choice == 1:
            obj.insert(key, data, "linear")
        elif choice == 2:
            obj.insert(key, data, "quadratic")
        elif choice == 3:
            method = input("Search method (linear/quadratic): ").lower()
            result = obj.search(key, data, method)
            print("Found at index" if result is not None else "Not found")

menu()

