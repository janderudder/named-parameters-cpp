#include <iostream>

/**
 *  Example options class
 */
struct File_options
{
    bool    read_only   {false};
    bool    create      {true};
};


/**
 *  Example business class,
 *  composed of the previous structure.
 */
struct File
{
    File_options    options;

    constexpr File(File_options opts) noexcept
        : options {opts}
    {}
};


/**
 *  Base for our named-parameters-simulation class.
 *  Just so we don't rewrite the following every time.
 */
template <typename T>
struct named_params_base
{
    T options;

    constexpr operator T const&() const noexcept
    {
        return options;
    }
};


/**
 *  Expose this undefined type to be specialized.
 *  Mainly for syntactic reasons, see [1] in example() below
 */
template <typename T>
struct named_params;


/**
 *  Our main type : a specialization to handle the File_options class
 */
template <>
struct named_params<File_options> : named_params_base<File_options>
{
    using self = named_params<File_options>;

    self& read_only(bool b)  { options.read_only = b; return *this; }
    self& create(bool b)     { options.create = b; return *this; }
};


/**
 *  Usage example
 */
void example()
{
    File file {
        named_params<File_options>{} // [1] syntax is explicit about the target type
        .create     (true)
        .read_only  (false)
    };

    std::boolalpha(std::cout);
    std::cout << file.options.read_only << "\n";    // false
    std::cout << file.options.create << "\n";       // true

}
