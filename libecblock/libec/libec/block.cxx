module libec.block;

blocks::blocks(uint32_t block_idx, std::string_view data)
    : index_(block_idx)
    , data_(data)
{
}
