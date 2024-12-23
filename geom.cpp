#include <bits/stdc++.h>

using namespace std;

constexpr long double PI = M_PI;
constexpr long double EPSILON = 1e-6;
constexpr long double DINF = std::numeric_limits<long double>::infinity();
constexpr int INF = 1e9;

template<typename T, T EPS>
int sign(T x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

long double rad2deg(long double angle) {
    return angle * 180 / PI;
}

// я сам в афиге, но я пишу шаблон на будущее
template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Vect {
    CordType x = CordINF, y = CordINF;

    Vect() = default;

    Vect(CordType x, CordType y) : x(x), y(y) {}
    Vect(Vect const &a) : x(a.x), y(a.y) {}
    Vect(Vect a, Vect b) : x(b.x - a.x), y(b.y - a.y) {}

    Vect operator+(Vect other) const {
        return {x + other.x, y + other.y};
    }

    Vect operator-(Vect other) const {
        return {x - other.x, y - other.y};
    }

    Vect operator*(CordType scale) const {
        return {x * scale, y * scale};
    }

    Vect operator-() const {
        return {-x, -y};
    }

    Vect<FloatType, FloatType, FloatType, DINF, EPSILON>
    operator/(CordType scale) const { // тут типа должен CordType стать long double
        return Vect<FloatType, FloatType, FloatType, DINF, EPSILON>((FloatType) x / scale, (FloatType) y / scale);
    }

    Vect<FloatType, FloatType, FloatType, DINF, EPSILON> norm() const {
        return Vect<FloatType, FloatType, FloatType, DINF, EPSILON>((FloatType) x / len(), (FloatType) y / len());
    }

    Vect perp() const {
        return Vect(y, -x);
    }

    LCordType operator*(Vect other) const {
        return (LCordType) x * other.x + (LCordType) y * other.y;
    }

    LCordType operator%(Vect other) const {
        return (LCordType) x * other.y - (LCordType) other.x * y;
    }

    LCordType len2() const {
        return (LCordType) x * x + (LCordType) y * y;
    }

    FloatType len() const {
        return sqrt(len2());
    }

    FloatType dist(Vect p) const {
        return Vect(*this, p).len();
    }

    bool operator==(Vect other) const {
        return (x == other.x || abs(x - other.x) <= CordEPS) && (y == other.y || abs(y - other.y) <= CordEPS);
    }

    bool operator!=(Vect other) const {
        return !(*this == other);
    }
};

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Line {
    CordType A = CordINF, B = CordINF, C = CordINF;
    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start, end;

    Line() = default;

    Line(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start,
         Vect<CordType, LCordType, FloatType, CordINF, CordEPS> end) : A(end.y - start.y), B(start.x - end.x),
                                                                       C((start.y - end.y) * start.x +
                                                                         (end.x - start.x) * start.y), start(start),
                                                                       end(end) {}

    Line(CordType A, CordType B, CordType C) : A(A), B(B), C(C) {
        //start = Vect<FloatType, FloatType, FloatType, CordINF, CordEPS>();
    } // прикрутить две точки на прямой

    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> norm() const {
        return Vect<CordType, LCordType, FloatType, CordINF, CordEPS>(A, B);
    }

    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> dir() const {
        return Vect<CordType, LCordType, FloatType, CordINF, CordEPS>(-B, A);
    }

    bool parallel(Line other) const {
        return abs((LCordType) A * other.B - (LCordType) other.A * B) <= CordEPS;
    }

    bool intersect(Line other) const {
        return !parallel(other);
    }

    bool operator==(Line other) const {
        return parallel(other) && abs((LCordType) A * other.C - (LCordType) other.A * C) <= CordEPS;
    }

    bool operator!=(Line other) const {
        return !(*this == other);
    }

    bool intersect(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return signdist(p) == 0;
    }

    Vect<FloatType, FloatType, FloatType, DINF, EPSILON>
    intersection(
            Line other) const { // начиная отсюда, координаты уже должны быть нецелыми, потому что, ну а что вы хотели
        if (parallel(other)) return {};
        return Vect<FloatType, FloatType, FloatType, DINF, EPSILON>(
                ((LCordType) (other.C) * B - (LCordType) C * other.B),
                (CordType) ((LCordType) (C) * other.A - (LCordType) other.C * A)) / (A * other.B - other.A * B);
    }

    FloatType dist(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return abs((A * p.x + B * p.y + C) / norm().len());
    }

    FloatType dist(Line l) const {
        if (!parallel(l)) return 0;
        return dist(l.start);
    }

    int signdist(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return sign<CordType, CordEPS>(A * p.x + B * p.y + C);
    }

    int signdist(Line l) const {
        if (!parallel(l)) return 0;
        return sign<CordType, CordEPS>(A * l.start.x + B * l.start.y + C);
    }

    Vect<FloatType, FloatType, FloatType, DINF, EPSILON> sim(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        Vect<FloatType, FloatType, FloatType, DINF, EPSILON> fp(p.x, p.y);
        return fp - norm().norm() * dist(p) * signdist(p) * 2;
    }
};

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Ray {
    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start, end;
    Ray() = default;
    Ray(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start,
        Vect<CordType, LCordType, FloatType, CordINF, CordEPS> end) : start(start), end(end) {}

    bool intersect(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return abs(Vect(p, start) % Vect(p, end)) <= CordEPS &&
               sign<CordType, CordEPS>(Vect(start, p) * Vect(start, end)) >= 0;
    }

    bool intersect(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const { // плохо, но я лучше не придумал
        if (l.signdist(start) * l.signdist(end) <= 0) return true;
        // return (l.dist(start) > l.dist(end));
        return abs(l.A * start.x + l.B * start.y + l.C) > abs(l.A * end.x + l.B * end.y + l.C);
    }

    bool intersect(Ray r) const {
        // обожаю, как же я обожаю
        Line l2 = Line<CordType, LCordType, FloatType, CordINF, CordEPS>(r.start,
                                                                         r.end), l1 = Line<CordType, LCordType, FloatType, CordINF, CordEPS>
                (start, end);
        if (l2.intersect(start) && l2.intersect(end)) {
            return !((sign<CordType, CordEPS>(Vect(start, end) * Vect(start, r.end)) == -1 &&
                      sign<CordType, CordEPS>(Vect(r.start, end) * Vect(r.start, r.end)) == -1 &&
                      sign<CordType, CordEPS>(Vect(start, end) * Vect(start, r.start)) == -1));
        }
        return intersect(l2) && r.intersect(l1);
    }

    FloatType dist(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        if (sign<CordType, CordEPS>(Vect(start, p) * Vect(start, end)) == 1) return Line(start, end).dist(p);
        return start.dist(p);
    }

    FloatType dist(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const {
        if (intersect(l)) return 0;
        return l.dist(start);
    }

    FloatType dist(Ray r) const {
        if (intersect(r)) return 0;
        return min(r.dist(start), dist(r.start));
    }
};

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Segment {
    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start, end;

    Segment() = default;
    Segment(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> start,
            Vect<CordType, LCordType, FloatType, CordINF, CordEPS> end) : start(start), end(end) {}

    bool intersect(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return sign<CordType, CordEPS>(Vect(p, start) % Vect(p, end)) == 0 &&
               sign<CordType, CordEPS>(Vect(p, start) * Vect(p, end)) <= 0;
    }

    bool intersect(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const {
        return l.signdist(start) * l.signdist(end) <= 0;
    }

    bool intersect(Ray<CordType, LCordType, FloatType, CordINF, CordEPS> r) const { // ох как лень думать...
        return r.intersect(Ray(start, end)) && r.intersect(Ray(end, start));
    }

    bool intersect(Segment r) const { // ох как лень думать...
        if (r.start == r.end) return intersect(r.start);
        if (start == end) return r.intersect(start);
        return intersect(Ray(r.start, r.end)) && intersect(Ray(r.end, r.start));
    }

    FloatType dist(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        if (sign<CordType, CordEPS>(Vect(start, p) * Vect(start, end)) == 1) {
            if (sign<CordType, CordEPS>(Vect(end, p) * Vect(end, start)) == 1) {
                return Line(start, end).dist(p);
            }
            return end.dist(p);
        }
        return start.dist(p);
    }

    FloatType dist(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const {
        if (intersect(l)) return 0;
        return min(l.dist(start), l.dist(end));
    }

    FloatType dist(Ray<CordType, LCordType, FloatType, CordINF, CordEPS> r) const {
        if (intersect(r)) return 0;
        return min({r.dist(start), r.dist(end), dist(r.start)});
    }

    FloatType dist(Segment s) const {
        if (intersect(s)) return 0;
        return min({s.dist(start), s.dist(end), dist(s.start), dist(s.end)});
    }
};

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Angle {
    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> a, o, b;

    Angle() = default;

    Angle(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> a,
          Vect<CordType, LCordType, FloatType, CordINF, CordEPS> o,
          Vect<CordType, LCordType, FloatType, CordINF, CordEPS> b) : a(a), o(o), b(b) {}

    Angle(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> a,
          Vect<CordType, LCordType, FloatType, CordINF, CordEPS> b) :
          a(a), o(Vect<CordType, LCordType, FloatType, CordINF, CordEPS>(0, 0)), b(b) {}

    explicit Angle(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> b) :
                    a(Vect<CordType, LCordType, FloatType, CordINF, CordEPS>(1, 0)),
                    o(Vect<CordType, LCordType, FloatType, CordINF, CordEPS>(0, 0)), b(b) {}

    FloatType value() const {
        if (sign<CordType, CordEPS>(Vect(o, a) % Vect(o, b)) >= 0) {
            return atan2(Vect(o, a) % Vect(o, b), Vect(o, a) * Vect(o, b));
        } else {
            return 2 * PI + atan2(Vect(o, a) % Vect(o, b), Vect(o, a) * Vect(o, b));
        }
    }

    FloatType geom_value() const {
        return abs(atan2(Vect(o, a) % Vect(o, b), Vect(o, a) * Vect(o, b)));
    }

    bool in(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return sign<CordType, CordEPS>(Vect(o, a) % Vect(o, p)) * sign<CordType, CordEPS>(Vect(o, a) % Vect(o, b)) >= 0 &&
                sign<CordType, CordEPS>(Vect(o, b) % Vect(o, p)) * sign<CordType, CordEPS>(Vect(o, b) % Vect(o, a)) >= 0;
    }

    Line <FloatType, FloatType, FloatType, DINF, EPSILON> bisect() const {
        Vect <FloatType, FloatType, FloatType, DINF, EPSILON> fo(o.x, o.y); // дожили до правды
        return Line(fo, fo + Vect(o, a).norm() + Vect(o, b).norm());
    }
};
template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
struct Circle {
    Vect<CordType, LCordType, FloatType, CordINF, CordEPS> center;
    CordType r; // я подумаю, вводить ли тип длины окружности, но если там нецелое, то наверное и корды нецелые

    Circle(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> center, CordType len) : center(center), r(len) {}
    Circle(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> center,
            Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) :center(center), r(center.dist(p)) {}

    FloatType area() const {
        return PI * r * r;
    }

    FloatType len() const {
        return 2 * PI * r;
    }

    FloatType dist(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) const {
        return center.dist(p) - r; // хитро, я знаю
    }

    FloatType dist(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const {
        return l.dist(center) - r; // хитро, я знаю
    }

    FloatType dist(Ray<CordType, LCordType, FloatType, CordINF, CordEPS> ray) const {
        return ray.dist(center) - r; // хитро, я знаю
    }

    FloatType dist(Segment<CordType, LCordType, FloatType, CordINF, CordEPS> s) const {
        return s.dist(center) - r; // хитро, я знаю
    }

    pair<Vect<FloatType, FloatType, FloatType, DINF, EPSILON>, Vect<FloatType, FloatType, FloatType, DINF, EPSILON>>
    intersection(Line<CordType, LCordType, FloatType, CordINF, CordEPS> l) const {
        if (dist(l) > 0)
            return {Vect<FloatType, FloatType, FloatType, DINF, EPSILON>(), Vect<FloatType, FloatType, FloatType, DINF, EPSILON>()};

        Vect<FloatType, FloatType, FloatType, DINF, EPSILON> fc(center.x, center.y),
                        p = fc - l.norm().norm() * l.dist(center) * l.signdist(center);
        if (dist(l) == 0) return {p, Vect<FloatType, FloatType, FloatType, DINF, EPSILON>()};
        FloatType h = l.dist(center), s = sqrt(r * r - h * h);
        return {p - l.dir().norm() * s, p + l.dir().norm() * s};
    }

    Line<CordType, LCordType, FloatType, CordINF, CordEPS> radaxis(Circle c) const {
        return Line<CordType, LCordType, FloatType, CordINF, CordEPS>(2 * (c.center.x - center.x),
                                                                      2 * (c.center.y - center.y),
                                                                      center.x * center.x + center.y * center.y -
                                                                      c.center.x * c.center.x -
                                                                      c.center.y * c.center.y +
                                                                      c.r * c.r - r * r);
    }

    LCordType power(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) {
        return Vect(p, center).len2() - r*r;
    }

    pair<Vect<FloatType, FloatType, FloatType, DINF, EPSILON>, Vect<FloatType, FloatType, FloatType, DINF, EPSILON>>
    tangents(Vect<CordType, LCordType, FloatType, CordINF, CordEPS> p) { // нет, я ни капли не жалею об этом
        Vect<FloatType, FloatType, FloatType, DINF, EPSILON> fp(p.x, p.y), fo(center.x, center.y);
        if (sign<LCordType, CordEPS>(power(p)) == -1) return {};
        if (sign<LCordType, CordEPS>(power(p)) == 0) return {fp, Vect<FloatType, FloatType, FloatType, DINF, EPSILON>()};

        Circle<FloatType, FloatType, FloatType, DINF, EPSILON> fthis(fo, r), fc(fp, sqrt(power(p)));
        return fthis.intersection(fthis.radaxis(fc));
    }
};

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
istream &operator>>(istream &in, Vect<CordType, LCordType, FloatType, CordINF, CordEPS> &v) {
    in >> v.x >> v.y;
    return in;
}

template<typename CordType, typename LCordType, typename FloatType, CordType CordINF, CordType CordEPS>
ostream &operator<<(ostream &out, Vect<CordType, LCordType, FloatType, CordINF, CordEPS> v) {
    out << v.x << " " << v.y;
    return out;
}
