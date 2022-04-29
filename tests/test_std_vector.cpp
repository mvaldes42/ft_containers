#include <vector>
#include <iostream>

void test_vector_construct()
{
    std::vector<int> first;                                // empty vector of ints
    std::vector<int> second (4,100);                       // four ints with value 100
    std::vector<int> third (second.begin(),second.end());  // iterating through second
    std::vector<int> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void test_vector_operator()
{
    std::vector<int> foo (3,0);
    std::vector<int> bar (5,0);

    bar = foo;
    foo = std::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void	test_vector_iterators()
{
    std::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "iterator comparison:" << std::endl;

  std::vector<int>::iterator       it = myvector.begin();
  std::vector<int>::const_iterator c_it = myvector.begin();
  it++;

  if (it > c_it)
    std::cout << "it is greater" << std::endl;
  else
    std::cout << "C_it is greater" << std::endl;  
}

void	test_vector_reverse_iterators()
{
    std::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  std::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void test_vector_size()
{
    std::vector<int> myvector;
	std::cout << "\nsize of empty container : " << myvector.size() << '\n';

	for (int i=0; i<10; i++) myvector.push_back(i);
	std::cout << "size after 10 push back : " << myvector.size() << '\n';

	myvector.insert (myvector.end(),10,100);
	std::cout << "size after inserting 10 elements : " << myvector.size() << '\n';

	myvector.pop_back();
	std::cout << "size after a pop back : " << myvector.size() << '\n';

	myvector.resize(12);
	std::cout << "size after resize to 12 : " << myvector.size() << '\n';

	myvector.resize(15);
	std::cout << "size after resize to 15 : " << myvector.size() << '\n';

	if(!myvector.empty())
		std::cout << "container is not empty" << '\n';

	myvector.clear();
	std::cout << "size after clear: " << myvector.size() << '\n';

	if(myvector.empty())
		std::cout << "container is empty\n" << '\n';
}

void test_vector_capacity()
{
    std::vector<int> myvector;

    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << (int) myvector.size() << '\n';
    std::cout << "capacity: " << (int) myvector.capacity() << '\n';
    std::cout << "max_size: " << (int) myvector.max_size() << '\n';

    for (int i=0; i<50; i++) myvector.push_back(i);
	std::cout << "\nafter 50 push_back : \n";
	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";

    std::cout << "\nafter reserve 250 : \n";

	myvector.reserve(250);
	std::cout << "size: " << myvector.size() << "\n";
	std::cout << "capacity: " << myvector.capacity() << "\n";
	std::cout << "max_size: " << myvector.max_size() << "\n";
}

void test_vector_operator_access()
{
    std::vector<int> myvector (10);   // 10 zero-initialized elements

  std::vector<int>::size_type sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void test_vector_operator_at()
{
    std::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
}

void test_vector_operator_front_back()
{
    std::vector<int> myvector;

    myvector.push_back(78);
    myvector.push_back(16);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void	test_vector_modifiers_add()
{
    std::cout << "\nassigning in differents way\n\n";
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	std::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';

	std::cout << "\nMy vector " << '\n';
	for (std::vector<int>::iterator it = first.begin() ; it != first.end(); ++it)
		std::cout << ' ' << *it;

	first.push_back(15);

	std::cout << "\nAfter push back 15" << '\n';
	for (std::vector<int>::iterator it = first.begin() ; it != first.end(); ++it)
		std::cout << ' ' << *it;
	
	std::cout << "\nAfter pop back" << '\n';
	first.pop_back();
	for (std::vector<int>::iterator it = first.begin() ; it != first.end(); ++it)
		std::cout << ' ' << *it;
}

void	test_vector_modifiers_insert()
{
    std::vector<int> myvector (3,100);
	std::vector<int>::iterator itt;

	itt = myvector.begin();
	itt = myvector.insert ( itt , 200 );

	myvector.insert (itt,2,300);

	// "it" no longer valid, get a new one:
	itt = myvector.begin();

	std::vector<int> newvector (2,400);
	myvector.insert (itt+2,newvector.begin(),newvector.end());

	int stdarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), stdarray, stdarray+3);

	std::cout << "\nmyvector contains:";
	for (itt=myvector.begin(); itt<myvector.end(); itt++)
		std::cout << ' ' << *itt;
	std::cout << '\n';
}

void test_vector_modifiers_delete()
{
    std::vector<int> myvector;
	for (int i=1; i<=10; i++) myvector.push_back(i);
	std::cout << "\n\n myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	myvector.erase (myvector.begin()+5);
	myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "\n myvector contains after erase:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
    
    std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (5,200);   // five ints with a value of 200

	std::cout << "\noriginal std foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "original std bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	foo.swap(bar);

	std::cout << "after swap std foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "after swap std bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	foo.clear();
	std::cout << "\nstd foo size after clear = " << foo.size();
}

void test_vector_allocator()
{
    std::vector<int> myvector;
    int * p;
    unsigned int i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p,5);
}

void test_vector_relational_operator()
{
    std::vector<int> foo (3,100);   // three ints with a value of 100
  std::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void test_vector_swap()
{
  std::vector<int> foo (3,100);   // three ints with a value of 100
  std::vector<int> bar (5,200);   // five ints with a value of 200

  std::vector<int>::iterator  it_foo = foo.begin();
  std::vector<int>::iterator  it_bar = bar.begin();
  
  std::cout << "foo_it = " << *it_foo << std::endl;
  std::cout << "bar_it = " << *it_bar << std::endl;

  foo.swap(bar);
  std::cout << "swapped !" << std::endl;

  std::cout << "foo_it = " << *it_foo << std::endl;
  std::cout << "bar_it = " << *it_bar << std::endl;

  it_foo++;
  it_bar++;

  it_foo--;
  it_bar--;

  std::cout << "foo contains:";
  for (std::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (std::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

