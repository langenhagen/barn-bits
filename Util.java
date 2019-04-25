/* Fisher-Yates
 */
static void shuffleArray(int[] arr) {

    for (int i = 0; i < arr.length; ++i) {

        int randomIndex = (int)random(i+1);
        int tmp = arr[randomIndex];
        arr[randomIndex] = arr[i];
        arr[i] = tmp;
    }
}
