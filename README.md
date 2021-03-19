# my_tar

## Description

my_tar is a command to manipulate tape archive.   
You can create tar archive with different options (-c, -r, -u), and you can view archieve's content

## Run Instructions
to run inside my_archive folder:  
        `make`  

## Test instructions
-c  
Create a new archive containing the example items:  
        `./my_tar -cf test_archive.tar list_archive.c conversion.c`  


-t  
To view a detailed table of contents for the archive:  
        `./my_tar -tf test_archive.tar`  

-r  
Like -c, but new entries are appended to the archive. The -f option is required.  
        `./my_tar -rf test_archive.tar my.c`

-u  
Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.  
        `./my_tar -uf test_archive.tar conversion.c extract_archive.c`  

