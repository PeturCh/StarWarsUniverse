template <typename K,typename V>
class DictionaryPair
{
    private:
    K key;
    V value;

    public:
    DictionaryPair() {}

    DictionaryPair(K _key, V _value) : key(_key), value(_value) {}

    V getValue() const 
    {
        return value;
    }

    K getKey() const 
    {
        return key;
    }

    void setValue(const V &_value)
    {
        value = _value;
    }
};