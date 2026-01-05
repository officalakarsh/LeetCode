long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long sum = 0;
    int negCount = 0;
    int minAbs = INT_MAX;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            int val = matrix[i][j];

            if (val < 0)
                negCount++;

            int absVal = val < 0 ? -val : val;
            sum += absVal;

            if (absVal < minAbs)
                minAbs = absVal;
        }
    }

    if (negCount % 2 != 0)
        sum -= 2LL * minAbs;

    return sum;
}
