#include "test_std_map.cpp"
#include "test_std_stack.cpp"
#include "test_std_vector.cpp"


int main()
{
	std::cout << "Testing std" << std::endl;

    //vector
	test_vector_construct();
	test_vector_operator();
	test_vector_iterators();
    test_vector_reverse_iterators();
	test_vector_size();
	test_vector_capacity();
	test_vector_operator_access();
    test_vector_operator_at();
	test_vector_operator_front_back();
	test_vector_modifiers_add();
	test_vector_modifiers_insert();
	test_vector_modifiers_delete();
    test_vector_allocator();
    test_vector_relational_operator();
    test_vector_swap();
	
    //stack
	std::cout << "\033[1;33m \nEntering Stack Test ... \033[0m\n";
    test_stack_constructor();
	test_stack_empty();
	test_stack_size();
	test_stack_top();
	test_stack_push_pop();

    //map
	std::cout << "\033[1;33m \nEntering Map Test ... \033[0m\n";
	test_map_construct();
	test_map_operator();
	test_map_iterator();
	test_map_capacity();
    test_max_size();
	test_map_operator_access();
	test_map_modifiers_insert_erase();
	test_map_modifiers();
    test_map_observers_key_comp();
    test_map_observers_value_comp();
    test_map_operation_find();
	test_map_operation_count();
	test_map_lower_upper();
    test_map_equal();
	test_map_allocator();
	test_map_relational_operator();

	return 0;
}