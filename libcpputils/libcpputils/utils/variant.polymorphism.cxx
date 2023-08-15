import<iostream>;
// import<variant>;
import<vector>;

#include <variant>
class Coord
{
  std::uint16_t lenght = 0;

public:
  Coord() = default;
  constexpr explicit Coord(std::uint16_t point)
      : lenght{ point }
  {
  }
  explicit constexpr operator std::uint16_t() const { return lenght; }
  constexpr auto
  operator<=>(const Coord &) const noexcept = default;
  constexpr auto
  operator+=(const Coord &rhs) -> std::uint16_t
  {
    return this->lenght += rhs.lenght;
  }
  constexpr auto
  operator+(const Coord &rhs) noexcept -> std::uint16_t
  {
    return *this += rhs;
  }
};
class Circle
{
private:
  int rad;
  Coord center{};

public:
  Circle(Coord c, int r)
      : rad{ r }
      , center{ c }
  {
  }
  void
  move(const Coord &c)
  {
    center += c;
  }
  void
  draw() const
  {
    std::cout << "circle at " << static_cast<std::uint16_t>(center)
              << " with radius " << rad << '\n';
  }
};
class Line
{
private:
  Coord m_left_side{};
  Coord m_right_side{};

public:
  Line(Coord left_side, Coord right_side)
      : m_left_side{ left_side }
      , m_right_side{ right_side }
  {
  }
  void
  draw() const
  {
    std::cout << "Line of " << static_cast<std::uint16_t>(m_left_side)
              << "m at left_side and "
              << static_cast<std::uint16_t>(m_right_side) << "m at right_side"
              << '\n';
  }
};
using poly_variant = std::variant<Line, Circle>;
auto
make_plane_figure() -> std::vector<poly_variant>
{
  auto figure_part = std::vector<poly_variant>();
  figure_part.emplace_back(Line(Coord{ 3 }, Coord{ 4 }));
  figure_part.emplace_back(Circle(Coord{ 1 }, 3));
  return figure_part;
}
auto
polymorphic_variant() noexcept -> void
{
  try
    {
      const auto figure = make_plane_figure();
      for (auto &&parts : figure)
        {
          std::cout << "index : " << parts.index() << '\n';
          std::visit([](auto &&variant) { variant.draw(); }, parts);
        }
    }
  catch (const std::bad_variant_access &exception)
    {
      std::cout << "EXCEPTION : " << exception.what() << '\n';
    }
}
