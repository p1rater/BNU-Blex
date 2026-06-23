# Blex OS Continuous Development Cycle

### Task: Continuous Kernel Optimization
1. **Analysis:** Scan the code in `/home/p1radev/BNU-Blex/src` and identify the most recently modified file.
2. **Static Analysis:** Find lines in the selected file that may pose a risk of `undefined behavior` or memory leaks.
3. **Refactoring:** Replace the identified risky or optimizeable parts with more efficient C code (Make suggestions and implement them with my approval).
4. **Compilation:** Run the command `make -C /home/p1radev/BNU-Blex`.
5. **Loop:** After completing this task, wait 5 minutes and **restart**.
