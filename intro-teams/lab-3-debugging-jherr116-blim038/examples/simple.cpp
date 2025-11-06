int main() {
    int *p = new int[10];
    p[9] = 1;

    delete[] p; // Deallocate the memory from the new above
    return 0;
}