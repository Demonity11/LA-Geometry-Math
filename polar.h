#ifndef POLAR_H
#define POLAR_H

#include "vector.h"

#include <iomanip>
#include <cassert>

namespace la
{
	struct Polar2D
	{
		float r{ 0.0f };
		float theta{ 0.0f };
	};

	struct Polar3D
	{
		float r{ 0.0f }; // sphere radius
		float h{ 0.0f }; // heading - initially pointing towards +z, rotates clockwise
		float p{ 0.0f }; // pitch   - initially pointing horizontally, rotates downward
	};

	struct Cyl3D
	{
		float r{ 0.0f };
		float theta{ 0.0f };
		float z{ 0.0f };
	};

	constexpr auto convertToCanonicalCoord(const Polar2D& p) -> Polar2D;
	constexpr auto convertToCanonicalCoord(const Polar3D& p) -> Polar3D;	

	constexpr auto convertVec2ToPolar2D(const Vec2& v)		 -> Polar2D;
	constexpr auto convertPolar2DToVec2(const Polar2D& p)	 -> Vec2;

	constexpr auto convertVec3ToPolar3D(const Vec3& v)		 -> Polar3D;
	constexpr auto convertPolar3DToVec3(const Polar3D& p)	 -> Vec3;

	constexpr auto convertVec3ToCyl3D(const Vec3& v)		 -> Cyl3D;
	constexpr auto convertCyl3DToVec3(const Cyl3D& c)		 -> Vec3;

	constexpr Polar2D convertToCanonicalCoord(const Polar2D& p)
	{
        constexpr float PI{ static_cast<float>(std::numbers::pi) };
		constexpr float twoPI{ 2.0f * PI };

		if (std::abs(p.r) < FLT_EPSILON)
		{
			return Polar2D{ 0.0f, 0.0f };
		}

		Polar2D result{ p };

		if (result.r < 0.0f)
		{
			result.r = -result.r;
			result.theta += PI;
		}

        result.theta += PI;
        result.theta -= std::floor(result.theta / twoPI) * twoPI;
        result.theta -= PI;

        if (result.theta <= -PI + 1e-5f || result.theta > PI)
        {
            result.theta = PI;
        }

		return result;
	}

	constexpr Polar3D convertToCanonicalCoord(const Polar3D& p)
	{
		if (std::abs(p.r) < FLT_EPSILON)
		{
			return Polar3D{ 0.0f, 0.0f, 0.0f };
		}

		constexpr float PI{ static_cast<float>(std::numbers::pi) };
		constexpr float twoPI{ 2.0f * PI };
		constexpr float PIOverTwo{ PI / 2.0f };

		Polar3D result{ p };

		if (p.r < 0.0f)
		{
			result.r = -result.r;
			result.h += PI;
			result.p = -result.p;
		}

		if (std::abs(result.p) > PIOverTwo)
		{
			result.p += PIOverTwo;
			result.p -= std::floor(result.p / twoPI) * twoPI;

			if (result.p > PI)
			{
				result.h += PI;
				result.p = 3.0f * PIOverTwo - result.p;
			}
			else
			{
				result.p -= PIOverTwo;
			}
		}

		if (std::abs(result.p) >= PIOverTwo * 0.99999f)
		{
			result.h = 0.0f;
		}
		
		if (std::abs(result.h) > PI)
		{
			result.h += PI;
			result.h -= std::floor(result.h / twoPI) * twoPI;
			result.h -= PI;
		}

        else if (result.h < 0.0f && std::abs(result.h) - PI < 0.00001f)
        {
            result.h = PI;
        }

		return result;
	}

	constexpr Polar2D convertVec2ToPolar2D(const Vec2& v)
	{
        const float vLength{ v.length() };

		if (vLength < FLT_EPSILON)
		{
			return Polar2D{ 0.0f, 0.0f };
		}

		return Polar2D
		{ 
			vLength, 
			std::atan2(v.y, v.x) 
		};
	}

	constexpr Vec2 convertPolar2DToVec2(const Polar2D& p)
	{
		return Vec2
		{ 
			p.r * std::cos(p.theta), 
			p.r * std::sin(p.theta) 
		};
	}

	constexpr Polar3D convertVec3ToPolar3D(const Vec3& v)
	{
        // 1. Raio da esfera (distância euclidiana 3D)
        const float r{ v.length() }; // ou std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z)

        // Caso singular: Origem (0, 0, 0)
        if (r < FLT_EPSILON)
        {
            return Polar3D{ 0.0f, 0.0f, 0.0f };
        }

        // 2. Distância projetada no plano horizontal XZ
        const float dHorizontal{ std::sqrt(v.x * v.x + v.z * v.z) };

        // 3. Cálculo do Pitch: p = atan2(-y, dHorizontal)
        // O sinal negativo garante que olhar para cima (+y) resulte em pitch negativo
        const float p{ std::atan2(-v.y, dHorizontal) };

        // 4. Cálculo do Heading com tratamento de singularidade nos polos
        float h{ 0.0f };

        // Se não estivermos exatamente no polo vertical (+Y ou -Y)
        if (dHorizontal > FLT_EPSILON)
        {
            h = std::atan2(v.x, v.z); // Ordem estrita (x, z) para convenção Z-Forward / X-Right
        }

        return Polar3D{ r, h, p };
	}

	constexpr Vec3 convertPolar3DToVec3(const Polar3D& p)
	{
		return Vec3
		{
			 p.r * std::sin(p.h) * std::cos(p.p),
			-p.r * std::sin(p.p),
			 p.r * std::cos(p.h) * std::cos(p.p)
		};
	}

	constexpr Cyl3D convertVec3ToCyl3D(const Vec3& v)
	{
		if (v == Vec3{ 0.0f })
		{
			return Cyl3D{ 0.0f, 0.0f, 0.0f };
		}

		return Cyl3D
		{
			std::sqrt(v.x * v.x + v.y * v.y),
			std::atan2(v.y, v.x),
			v.z
		};
	}

	constexpr Vec3 convertCyl3DToVec3(const Cyl3D& c)
	{
		return Vec3
		{
			c.r * std::cos(c.theta),
			c.r * std::sin(c.theta),
			c.z
		};
	}
}

// =============================================================================
// HELPERS DE COMPARAÇÃO COM EPSILON E TRATAMENTO DE SINGULARIDADES
// =============================================================================
namespace test_utils_3d
{
    constexpr float EPSILON{ 1e-4f };
    constexpr float PI{ static_cast<float>(std::numbers::pi) };
    constexpr float HALF_PI{ PI * 0.5f };
    constexpr float TWO_PI{ 2.0f * PI };

    inline bool isClose(float a, float b, float eps = EPSILON)
    {
        return std::abs(a - b) <= eps;
    }

    inline bool isClosePolar3D(const la::Polar3D& p1, const la::Polar3D& p2, float eps = EPSILON)
    {
        // 1. Raio deve ser identico
        if (!isClose(p1.r, p2.r, eps)) return false;

        // 2. Se r == 0 (Origem), heading e pitch sao canonicamente 0
        if (isClose(p1.r, 0.0f, eps)) return true;

        // 3. Pitch deve ser identico em magnitude
        if (!isClose(p1.p, p2.p, eps)) return false;

        // 4. Singularidade nos Polos (|p| == pi/2): heading e arbitrario / fixado em 0
        if (isClose(std::abs(p1.p), HALF_PI, eps)) return true;

        // 5. Comparacao de Heading com Wrap-Around (-pi == +pi)
        float hDiff = std::abs(p1.h - p2.h);
        if (isClose(hDiff, TWO_PI, eps)) return true;

        return isClose(p1.h, p2.h, eps);
    }

    inline bool isCloseVec3(const la::Vec3& v1, const la::Vec3& v2, float eps = EPSILON)
    {
        return isClose(v1.x, v2.x, eps) &&
            isClose(v1.y, v2.y, eps) &&
            isClose(v1.z, v2.z, eps);
    }
}

// =============================================================================
// 1. TESTES DE FORMA CANÔNICA (convertToCanonicalCoord)
// =============================================================================
void testCanonicalCoord3D()
{
    using namespace test_utils_3d;
    std::cout << "[TEST] convertToCanonicalCoord (3D)...\n";

    // A. Ponto já Canônico
    {
        la::Polar3D p{ 5.0f, PI / 4.0f, PI / 6.0f };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClosePolar3D(res, { 5.0f, PI / 4.0f, PI / 6.0f }) && "Falha: Ponto canonico valido foi alterado.");
    }

    // B. Singularidade na Origem (r = 0) -> h e p devem ser resetados para 0
    {
        la::Polar3D p{ 0.0f, 1.23f, -0.45f };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClose(res.r, 0.0f) && isClose(res.h, 0.0f) && isClose(res.p, 0.0f) &&
            "Falha: Origem r=0 deve forcar h=0 e p=0.");
    }

    // C. Raio Negativo (r < 0)
    // r = -4, h = 0, p = 0 -> Inverte para r = 4, h = +PI, p = 0
    {
        la::Polar3D p{ -4.0f, 0.0f, 0.0f };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClose(res.r, 4.0f) && isClose(res.h, PI) && isClose(res.p, 0.0f) &&
            "Falha: Raio negativo nao inverteu h para PI.");
    }

    // D. Raio Negativo com Pitch
    // r = -2, h = PI/2 (+x), p = PI/4 (baixo) -> r = 2, h = -PI/2 (-x), p = -PI/4 (cima)
    {
        la::Polar3D p{ -2.0f, HALF_PI, PI / 4.0f };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClosePolar3D(res, { 2.0f, -HALF_PI, -PI / 4.0f }) &&
            "Falha: Raio negativo com pitch nao inverteu p e h.");
    }

    // E. Pitch Ultrapassando o Polo Inferior (Nadir Overshoot: p > PI/2)
    // Olhar 120 graus para baixo equivale a olhar 60 graus para baixo, mas virado para tras (h + PI)
    {
        la::Polar3D p{ 3.0f, 0.0f, (2.0f * PI) / 3.0f }; // p = 120 deg
        la::Polar3D res = la::convertToCanonicalCoord(p);
        // Esperado: p = 180 - 120 = 60 deg (PI/3), h = 0 + PI = PI
        assert(isClosePolar3D(res, { 3.0f, PI, PI / 3.0f }) &&
            "Falha: Overshoot do Nadir (p > PI/2) nao corrigiu pitch e heading.");
    }

    // F. Pitch Ultrapassando o Polo Superior (Zenith Undershoot: p < -PI/2)
    // Olhar 135 graus para cima equivale a olhar 45 graus para cima virado para tras
    {
        la::Polar3D p{ 3.0f, HALF_PI, -0.75f * PI }; // h = 90 deg, p = -135 deg
        la::Polar3D res = la::convertToCanonicalCoord(p);
        // Esperado: p = -45 deg (-PI/4), h = 90 - 180 = -90 deg (-HALF_PI)
        assert(isClosePolar3D(res, { 3.0f, -HALF_PI, -PI / 4.0f }) &&
            "Falha: Undershoot do Zenith (p < -PI/2) nao corrigiu pitch e heading.");
    }

    // G. Singularidade no Topo Estrito (Gimbal Lock no Zenith: p = -PI/2) -> h deve ser 0
    {
        la::Polar3D p{ 5.0f, 0.87f, -HALF_PI };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClose(res.r, 5.0f) && isClose(res.p, -HALF_PI) && isClose(res.h, 0.0f) &&
            "Falha: Gimbal Lock no Zenith deve fixar h=0.");
    }

    // H. Singularidade no Fundo Estrito (Gimbal Lock no Nadir: p = +PI/2) -> h deve ser 0
    {
        la::Polar3D p{ 5.0f, -1.54f, HALF_PI };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClose(res.r, 5.0f) && isClose(res.p, HALF_PI) && isClose(res.h, 0.0f) &&
            "Falha: Gimbal Lock no Nadir deve fixar h=0.");
    }

    // I. Heading Wrap-Around (h > PI ou h < -PI)
    {
        la::Polar3D p{ 2.0f, 3.0f * PI, PI / 6.0f }; // h = 3*PI equivale a PI
        la::Polar3D res = la::convertToCanonicalCoord(p);
        assert(isClosePolar3D(res, { 2.0f, PI, PI / 6.0f }) && "Falha: Wrap-around de h > PI.");
    }

    // J. Borda de Heading: h = -PI deve ser normalizado para +PI
    {
        la::Polar3D p{ 7.0f, -PI, 0.0f };
        la::Polar3D res = la::convertToCanonicalCoord(p);
        std::cout << "res.h = " << res.h << "\n";
        std::cout << "PI = " << PI << "\n";
        assert(isClose(res.h, PI) && "Falha: h = -PI estrito deve virar +PI.");
    }

    std::cout << "  -> PASSOU com sucesso!\n\n";
}

// =============================================================================
// 2. TESTES DE CONVERSÃO CARTESIANO -> ESFÉRICO 3D (convertVec3ToPolar3D)
// =============================================================================
void testVec3ToPolar3D()
{
    using namespace test_utils_3d;
    std::cout << "[TEST] convertVec3ToPolar3D...\n";

    // A. Origem
    {
        la::Vec3 v{ 0.0f, 0.0f, 0.0f };
        la::Polar3D res = la::convertVec3ToPolar3D(v);
        assert(isClose(res.r, 0.0f) && isClose(res.h, 0.0f) && isClose(res.p, 0.0f) &&
            "Falha: Vetor nulo nao gerou Polar3D(0,0,0).");
    }

    // B. Eixos Cardeais no Horizonte (p = 0)
    {
        // +Z Axis (North / Forward) -> h = 0, p = 0
        la::Polar3D pPosZ = la::convertVec3ToPolar3D(la::Vec3{ 0.0f, 0.0f, 5.0f });
        assert(isClosePolar3D(pPosZ, { 5.0f, 0.0f, 0.0f }) && "Falha no eixo +Z.");

        // +X Axis (East / Right) -> h = +PI/2, p = 0
        la::Polar3D pPosX = la::convertVec3ToPolar3D(la::Vec3{ 5.0f, 0.0f, 0.0f });
        assert(isClosePolar3D(pPosX, { 5.0f, HALF_PI, 0.0f }) && "Falha no eixo +X.");

        // -Z Axis (South / Back) -> h = +PI, p = 0
        la::Polar3D pNegZ = la::convertVec3ToPolar3D(la::Vec3{ 0.0f, 0.0f, -5.0f });
        std::cout << "pNegZ.r = " << pNegZ.r << "\n";
        std::cout << "pNegZ.h = " << pNegZ.h << "\n";
        std::cout << "pNegZ.p = " << pNegZ.p << "\n";
        assert(isClosePolar3D(pNegZ, { 5.0f, PI, 0.0f }) && "Falha no eixo -Z.");

        // -X Axis (West / Left) -> h = -PI/2, p = 0
        la::Polar3D pNegX = la::convertVec3ToPolar3D(la::Vec3{ -5.0f, 0.0f, 0.0f });
        assert(isClosePolar3D(pNegX, { 5.0f, -HALF_PI, 0.0f }) && "Falha no eixo -X.");
    }

    // C. Eixos Verticais Puros (Polos / Zenith & Nadir)
    {
        // +Y Axis (Zenith / Straight Up) -> p = -PI/2, h = 0
        la::Polar3D pUp = la::convertVec3ToPolar3D(la::Vec3{ 0.0f, 4.0f, 0.0f });
        assert(isClose(pUp.r, 4.0f) && isClose(pUp.p, -HALF_PI) && isClose(pUp.h, 0.0f) &&
            "Falha no eixo vertical +Y (Up).");

        // -Y Axis (Nadir / Straight Down) -> p = +PI/2, h = 0
        la::Polar3D pDown = la::convertVec3ToPolar3D(la::Vec3{ 0.0f, -4.0f, 0.0f });
        assert(isClose(pDown.r, 4.0f) && isClose(pDown.p, HALF_PI) && isClose(pDown.h, 0.0f) &&
            "Falha no eixo vertical -Y (Down).");
    }

    // D. Diagonais em Octantes Distintos (45 graus no plano XZ e elevacao)
    {
        const float sqrt2 = std::sqrt(2.0f);
        const float r = std::sqrt(3.0f); // Vetor [1, 1, 1] tem r = sqrt(3)

        // 1. [+1, +1, +1] -> Olhando para +X, +Z (h = +PI/4) e para CIMA (+Y => p < 0)
        // d_horizontal = sqrt(1^2 + 1^2) = sqrt(2). p = atan2(-y, d) = atan2(-1, sqrt(2))
        la::Polar3D pQ1Up = la::convertVec3ToPolar3D(la::Vec3{ 1.0f, 1.0f, 1.0f });
        float expectedPitchUp = -std::asin(1.0f / r);
        assert(isClose(pQ1Up.r, r) && isClose(pQ1Up.h, PI / 4.0f) && isClose(pQ1Up.p, expectedPitchUp) &&
            "Falha no octante (+X, +Y, +Z).");

        // 2. [+1, -1, +1] -> Olhando para +X, +Z (h = +PI/4) e para BAIXO (-Y => p > 0)
        la::Polar3D pQ1Down = la::convertVec3ToPolar3D(la::Vec3{ 1.0f, -1.0f, 1.0f });
        float expectedPitchDown = std::asin(1.0f / r);
        assert(isClose(pQ1Down.r, r) && isClose(pQ1Down.h, PI / 4.0f) && isClose(pQ1Down.p, expectedPitchDown) &&
            "Falha no octante (+X, -Y, +Z).");
    }

    std::cout << "  -> PASSOU com sucesso!\n\n";
}

// =============================================================================
// 3. TESTES DE CONVERSÃO ESFÉRICO 3D -> CARTESIANO (convertPolar3DToVec3)
// =============================================================================
void testPolar3DToVec3()
{
    using namespace test_utils_3d;
    std::cout << "[TEST] convertPolar3DToVec3...\n";

    // A. Origem
    {
        la::Polar3D p{ 0.0f, 0.0f, 0.0f };
        la::Vec3 res = la::convertPolar3DToVec3(p);
        assert(isCloseVec3(res, { 0.0f, 0.0f, 0.0f }) && "Falha: Polar (0,0,0) nao gerou Vec3(0,0,0).");
    }

    // B. Eixos Cardeais
    {
        // Heading 0, Pitch 0 -> aponta para +Z
        assert(isCloseVec3(la::convertPolar3DToVec3({ 3.0f, 0.0f, 0.0f }), { 0.0f, 0.0f, 3.0f }));

        // Heading +PI/2, Pitch 0 -> aponta para +X
        assert(isCloseVec3(la::convertPolar3DToVec3({ 3.0f, HALF_PI, 0.0f }), { 3.0f, 0.0f, 0.0f }));

        // Heading PI, Pitch 0 -> aponta para -Z
        assert(isCloseVec3(la::convertPolar3DToVec3({ 3.0f, PI, 0.0f }), { 0.0f, 0.0f, -3.0f }));

        // Heading -PI/2, Pitch 0 -> aponta para -X
        assert(isCloseVec3(la::convertPolar3DToVec3({ 3.0f, -HALF_PI, 0.0f }), { -3.0f, 0.0f, 0.0f }));

        // Heading qualquer, Pitch -PI/2 (Zenith) -> aponta para +Y
        assert(isCloseVec3(la::convertPolar3DToVec3({ 5.0f, 0.0f, -HALF_PI }), { 0.0f, 5.0f, 0.0f }));

        // Heading qualquer, Pitch +PI/2 (Nadir) -> aponta para -Y
        assert(isCloseVec3(la::convertPolar3DToVec3({ 5.0f, 0.0f, HALF_PI }), { 0.0f, -5.0f, 0.0f }));
    }

    // C. Ponto Inclinado (r=2, h=45 deg, p=30 deg para baixo)
    {
        // x = r * sin(h) * cos(p) = 2 * sin(45) * cos(30) = 2 * (sqrt(2)/2) * (sqrt(3)/2) = sqrt(6)/2
        // y = -r * sin(p) = -2 * sin(30) = -2 * 0.5 = -1.0
        // z = r * cos(h) * cos(p) = 2 * cos(45) * cos(30) = sqrt(6)/2
        la::Polar3D p{ 2.0f, PI / 4.0f, PI / 6.0f };
        la::Vec3 res = la::convertPolar3DToVec3(p);
        float expectedXZ = std::sqrt(6.0f) * 0.5f;

        assert(isCloseVec3(res, { expectedXZ, -1.0f, expectedXZ }) && "Falha na conversao analitica 3D.");
    }

    std::cout << "  -> PASSOU com sucesso!\n\n";
}

// =============================================================================
// 4. TESTE DE ISOMORFISMO BIDIRECIONAL (ROUND-TRIP TEST)
// =============================================================================
void testRoundTrip3D()
{
    using namespace test_utils_3d;
    std::cout << "[TEST] Round-Trip Invertibility (Cartesian <-> Polar3D)...\n";

    const la::Vec3 testVectors[] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 10.0f },
        { 10.0f, 0.0f, 0.0f },
        { 0.0f, 10.0f, 0.0f },
        { 0.0f, -10.0f, 0.0f },
        { 0.0f, 0.0f, -10.0f },
        { -10.0f, 0.0f, 0.0f },
        { 3.2f, 5.1f, 8.7f },
        { -4.5f, 2.3f, 6.1f },
        { 7.8f, -9.4f, 1.2f },
        { -6.3f, -8.1f, -4.7f },
        { 12.0f, -0.05f, 0.05f },
        { 0.01f, 15.0f, -0.02f }
    };

    for (const auto& vOriginal : testVectors)
    {
        // Vec3 -> Polar3D -> Vec3
        la::Polar3D polar = la::convertVec3ToPolar3D(vOriginal);
        la::Vec3 vReconstructed = la::convertPolar3DToVec3(polar);

        assert(isCloseVec3(vOriginal, vReconstructed, 1e-4f) &&
            "Falha de Round-Trip: Vec3 -> Polar3D -> Vec3 corrompeu os dados cartesianos!");
    }

    std::cout << "  -> PASSOU com sucesso!\n\n";
}

#endif