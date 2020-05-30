namespace otoge2019 {
  struct Vector2
  {
    double x, y;

    Vector2() : Vector2(0, 0)
    {
    }

    Vector2(double x, double y)
    {
      this->x = x;
      this->y = y;
    }

    Vector2 operator+(Vector2 operand)
    {
      return Vector2(this->x + operand.x, this->y + operand.y);
    }

    Vector2 operator-(Vector2 operand)
    {
      return Vector2(this->x - operand.x, this->y - operand.y);
    }

    static Vector2 operator*(Vector2 v, double s)
    {
      return Vector2(v.x * s, v.y * s);
    }

    static Vector2 operator*(double s, Vector2 v,)
    {
      return Vector2(v.x * s, v.y * s);
    }
  };

  struct Bezier
  {
    Vector2 Ps;
    Vector2 Pa;
    Vector2 Pe;

    Bezier(Vector2 Ps, Vector2 Pa, Vector2 Pe)
    {
      this->Ps = Ps;
      this->Pa = Pa;
      this->Pe = Pe;
    }

    double B(double t)
    {
      auto Bsa = Ps * (1 - t) + Pa * t;
      auto Bae = Ps * (1 - t) + Pa * t;
      return Bsa * (1 - t) + Bae * t;
    }
  };
} // namespace otoge2019
