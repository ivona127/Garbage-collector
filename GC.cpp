#include <iostream>
#include <string>
#include <vector>
#include "GC.h"

using namespace std;

vector <Page> GC::pages;


void GC::init(){
	Page page;
	pages.push_back(page);
           
    int pageNum =  pages.size() - 1;
            
    for(int byte = 0; byte < MAX_SIZE; byte++){
        pages[pageNum].data[byte] = '0';
    }
            
}

void* GC::allocate(size_t size){
    int empty = 0;
    int pageNum = 0;
    int index = 0;

    for(int page = 0; page < pages.size(); page++){
        for(int byte = 0; byte < MAX_SIZE; byte++){
        	if(pages[page].data[byte] == '0'){
            	empty = 1;
                for(int i = byte; i < size; i++){
                    if (pages[page].data[i] != '0' ){
                        byte = i;
                        empty = 0;
                        break;
                    }
                }
            }

            if (empty == 1){
                index = byte;
                pageNum = page;
                break;
            }

        }
    }

	void* initial_address;
    if (empty == 1){
    	initial_address = &pages[pageNum].data[index];
        Block block(initial_address, size);
        pages[pageNum].blocks.push_back(block);

        for(int i = index; i < index + size; i++){
            pages[pageNum].data[i] = '1';
        }

    } else {
        if (pages.size() < PAGES){
            init();
            allocate(size);
        } else {
            throw allocationFailed();
        }
    }
    return initial_address;
}

void GC::free(void *region){
    char *ptr;
    int valid = 0;
    int size = 0;
    for (int page = 0; page < pages.size(); page++){
        for (auto it = pages[page].blocks.begin(); it < pages[page].blocks.end(); it++){
            size = it->size;
            if (it->initial_address == region){
                valid = 1;
            }

            if (valid == 1){
                int i=0;
                ptr = (char*) region;
                while (size > 0){
                    *(ptr + i) = '0';
                    i++;
                    size--;
                }
                pages[page].blocks.erase(it);
            	break;
            }
        }
    }

    if (valid != 1){
        throw invalidAdress();
    }
}

void GC::grow(void *region, size_t size){
	char *ptr;
	int valid = 0;
    int block_size = 0;
            
    for (int page = 0; page < pages.size(); page++){
        for (auto it = pages[page].blocks.begin(); it < pages[page].blocks.end(); it++){
            if (!valid){
                block_size = it->size;
            }
            if (it->initial_address == region){
                it->size += size;
                valid = 1;
                int i = 0;
                while (i < size){
                    ptr = (char*) region + block_size + i;
                    if ( *ptr != '0'){
                        valid = 0;
                        break;
                    }
                    i++;
                }
            }
        }
    }
            
    if (!valid){
        throw invalidAdress();
    } else {
    	ptr = (char*) region + block_size;

        for(int page = 0; page < pages.size(); page++){
            for(int byte = 0; byte < MAX_SIZE; byte++){
                if( &pages[page].data[byte] == ptr){
                    int i = 0;
                    while (i < size){
                        pages[page].data[byte] = '1';
                        byte++;
                        i++;
                    }
                    break;
                }
            }
        }
    }
}

void GC::shrink(void *region, size_t size){
    char* ptr;
    int diff = 0;
    int valid = 0;

    for (int page = 0; page < pages.size(); page++){
        for (auto it = pages[page].blocks.begin(); it < pages[page].blocks.end(); it++){

            if (it->initial_address == region){
                if (it->size < size) {
                    throw invalidInput();
                }

                diff = it->size - size;

                if (diff == 0){
                    free(region);
                    break;
                } else if (diff < 0 ) {
                    throw invalidInput();
                } else {
                    int new_size = size;
                    valid = 1;
                    it->size = new_size;
                    ptr = (char*) region + new_size;

                    for(int page = 0; page < pages.size(); page++){
                        for(int byte = 0; byte < MAX_SIZE; byte++){
                            if( &pages[page].data[byte] == ptr){
                                int offset = 0;
                                while (offset < diff){
                                    pages[page].data[byte] = '0';
                                    byte++;
                                    offset++;
                                }
                                break;
                            }   
                        }
                    }
                }
            }
        }
    }

    if (!valid){
        throw invalidAdress();
    } 
}  
        
void GC::dump(string filepath){
    ofstream file = ofstream(filepath, ios::out);
  
    if(file.fail()){
        throw "Problem with file";
    }

    int counter = 0;
    for(int page = 0; page < pages.size(); page++){
        for(int byte = 0; byte < MAX_SIZE; byte++){
            if (pages[page].data[byte] != '0'){
                counter++;
            }
        }
    }

    file << counter  << " / " << MAX_SIZE << endl;

    char* ptr_end;
    for (int page = 0; page < pages.size(); page++){
        for (auto it = pages[page].blocks.begin(); it < pages[page].blocks.end(); it++){
            int i=0;
            while (i < it->size){
                ptr_end = (char*) it->initial_address + i;
                i++;
            }

            file << it->initial_address << " - " <<  (void*)ptr_end << "(" << it->size << ")" << endl;
        }
    }

    file.close();
}

/*
void GC::clean(){
    for (int page = 0; page < pages.size(); page++){
        for (auto it = pages[page].blocks.begin(); it < pages[page].blocks.end(); it++){
            delete[] it->initial_address;
        }
    }
}
*/