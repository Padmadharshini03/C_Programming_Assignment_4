# CSA02 – C Programming | Assignment 4 (CO4)
## Modelling Real-World Data with Structures and Unions

- **Student Name:** Padma Dharshini S D
- **Register Number:** 192521405
- **Programme:** B.Tech – Information Technology
- **Course:** CSA02 – C Programming (CO4)
- **Compiler & Version:** GCC 13+ (`gcc -Wall -Wextra -std=c11`)

### Repository Structure
- `Task01/task1_2.c` — Repaired Primary Health Centre patient register using nested `Date` and `BloodPressure` structures and pointer validation.
- `Task02/task2_complete.c` — Courier parcel tracking with nested structures, selection sort by weight, and `sizeof` swap byte analysis.
- `Task03/task3_complete.c` — Weather-station tagged union (`12 bytes` vs `20 bytes`) and IEEE-754 misuse experiment.
- `Task04/task4_repaired.c` — Structure forensics with memory address proof (`%p`) and pointer-based `addInterest()`.
- `Task05/task5_complete.c` — Hostel mess token counter comparing `static`, `auto`, `extern`, and `register` storage classes.
- `Task06/task6_canteen.c` — College canteen inventory and billing system using tagged unions, nested structs, stock checks, 2-day expiry alerts, and descending revenue summary.

### Compilation & Execution Steps
```bash
gcc -Wall -Wextra -std=c11 Task01/task1_2.c -o task1 && ./task1
gcc -Wall -Wextra -std=c11 Task02/task2_complete.c -o task2 && ./task2
gcc -Wall -Wextra -std=c11 Task03/task3_complete.c -o task3 && ./task3
gcc -Wall -Wextra -std=c11 Task04/task4_repaired.c -o task4 && ./task4
gcc -Wall -Wextra -std=c11 Task05/task5_complete.c -o task5 && ./task5
gcc -Wall -Wextra -std=c11 Task06/task6_canteen.c -o task6 && ./task6
```
