class Block{
    public:
		size_t size;
		void* initial_address;
        
        Block(void* initial_address, size_t size){
            this->initial_address = initial_address;
            this->size = size;
        }
};