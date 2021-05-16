template <typename K,typename V>
class DictionaryPair
{
    private:
    K key;
    V value;
    bool GMColour = false;

    public:
    DictionaryPair() {}

    DictionaryPair(K _key, V _value) : key(_key), value(_value) {}

    DictionaryPair(K _key, V _value, bool _GMColour) : key(_key), value(_value), GMColour(_GMColour) {}

    V getValue() const 
    {
        return value;
    }

    K getKey() const 
    {
        return key;
    }

    bool isGMColour()
    {
        return GMColour;
    }

    void setGMColour()
    {
        GMColour = true;
    }

    void setValue(const V &_value)
    {
        value = _value;
    }
};