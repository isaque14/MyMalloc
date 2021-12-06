namespace mymallinfo {

    struct mallinfo {
        int ordblks;  /* number of free chunks */
        int uordblks; /* total allocated space */
        int fordblks; /* total free space */
        int keepcost; /* top-most, releasable (via malloc_trim) space */
    };

    struct mallinfo mallinfo(void);
}