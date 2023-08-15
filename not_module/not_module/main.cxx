import<iostream>;
import intro;

auto
main() -> int
{
  const auto persons
      = std::vector{ persons_t{ .name = "Bernard", .age = 21 } };
  for (auto const &name :
       name_for(persons, [](persons_t person) { return person.age == 21; }))
    {
      std::cout << "name is " << name << '\n';
    }
}
