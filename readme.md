# Breached Project for EE462
Authored By: Colin Gasiwicz
### Project Goals
 - Create fast creation and searching of emails from breached password text file
 - Generate hashes for email and password and store them in `data/hashed.txt`
 - Fast search for hash in `data/hashedtxt` 
### Important Information
 - `/data` directory must contain `realCredentials.txt` in order for the program to work
 - executables and object files placed in `/build`
#### Usage of program
```
./breachedApp <email_string>
```
will make `data/hashed.txt` and write hashed data and search for <email_string> 
the user inputted argument of an email address to search for
### Sources used
 -  [cplusplus.com](https://cplusplus.com/) For c++ documentation on hash, thread, string, etc...
 - Various past stackoverflow posts about multiple issues with threading and hashing in C++
 - Course textbook code
 - Did the same project for another class
 - No AI used
### Challenges encountered
  - The operator function needs to be a non-static member function caused issues
  - Threads finding the hash and not stopping other threads
  - Threads not finding the hash
### Future Improvements
  - Utilizing a database to store this hashes would be less code and easier to expand and would make building a web ui possiable
  - An algorithmic approach to search for the data would speed up results further
  - Create a proper project directory for storing files
  - Using a `std::set` or `std::map` for storage of hashes