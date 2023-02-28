# Computer System

This repo contains my study notes and learning projects contained in the Ohio State University course CSE2431.

## Virtualization

1. Definition of an OS
   Software that converts hardware into a useful form for applications: Make sure the system operates correctly and efficiently in an easy to use manner.
2. What are the three "pieces" of every modern OS, and what is the basic description of each of them? What abstractions are associated with each of the 3 pieces?

- Virtualization  
  make the system behave so that each application can run as though it has certain critical resources to itself; i.e., make it believe it has exclusive use of each critical resource in the system (no sharing)  
  (⭕️related abstractions: process, address space)
- Concurrency  
  OS must be able to handle concurrent events which can interact  
  (related abstractions: locks, semaphores, condition variables, shared memory, critical sections)
- Persistence  
  preserve information permanently  
  (related files, directories, links)

3. What are some reasons cited in the class slides for studying operating systems?

- build, modify, or administer an OS
- behavior of OS impacts entire machine
- tune workload performance
- apply knowledge accross many layers(computer architecture, programming languages, data structure and algo, and performance modeling)
