# ObmanCPP
ObjectManager implementation in C++ (which is significantly faster)
# Building
```bash
mkdir build
cd build
cmake ..
make
```

Then add `object_manager/libobject_manager.so` to php.ini or use it in cli as `-dextension=object_manager/libobject_manager.so`

Now you can use the object manager. If you want to use it in a Magento 2 installation you need [additional wrapper](https://github.com/EgorDm/ObmanPHP)

## Documentation
WIP

## Requirements
* [PHP-CPP](http://www.php-cpp.com/) - Use [My fork for now](https://github.com/EgorDm/PHP-CPP)
