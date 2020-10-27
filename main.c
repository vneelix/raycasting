#include "engine.h"

float	Vec2fLength(float2 vec2f) {
	return sqrtf(
		vec2f.x * vec2f.x + vec2f.y * vec2f.y
	);
}

float	clamp(float value, float lhs, float rhs) {
	if (value >= lhs && value <= rhs) {
		return value;
	} else if (value < lhs) {
		return lhs;
	} else {
		return rhs;
	}
}

float	dot(float2 a, float2 b) {
	return a.x * b.x + a.y * b.y;
}

float2	normalize(float2 vec2f) {
	float vec2fLen = Vec2fLength(vec2f);
	return (float2){
		vec2f.x / vec2fLen,
		vec2f.y / vec2fLen
	};
}

float2	RotationVec2f(float2 vec2f, float alpha) {
	return (float2){
		vec2f.x * cosf(alpha) - vec2f.y * sinf(alpha),
		vec2f.x * sinf(alpha) + vec2f.y * cosf(alpha)
	};
}

float2	LineLineIntersection(float2 a, float2 b, float2 c, float2 d) {
	// Line AB represented as a1x + b1y = c1
	float a1 = b.y - a.y;
	float b1 = a.x - b.x;
	float c1 = a1 * a.x + b1 * a.y;
	// Line CD represented as a2x + b2y = c2
	float a2 = d.y - c.y;
	float b2 = c.x - d.x;
	float c2 = a2 * c.x + b2 * c.y;

	float determinant = a1 * b2 - a2 * b1;

	if (determinant != 0.f) {
		return (float2){
			(b2 * c1 - b1 * c2) / determinant,
			(a1 * c2 - a2 * c1) / determinant
		};
	} else {
		return (float2){
			INFINITY,
			INFINITY
		};
	}
}

float2	LineProjection(float2 a, float2 b, float2 c) {
	// Line AB represented as a1x + b1y = c1
	float a1 = b.y - a.y;
	float b1 = a.x - b.x;
	float c1 = a1 * a.x + b1 * a.y;
	// Normal Line represented as a2x + b2y = c2
	float a2 = b1;
	float b2 = -a1;
	float c2 = b1 * c.x - a1 * c.y;

	float determinant = a1 * b2 - a2 * b1;

	if (determinant != 0.f) {
		return (float2){
			(b2 * c1 - b1 * c2) / determinant,
			(a1 * c2 - a2 * c1) / determinant
		};
	} else {
		return (float2){
			INFINITY,
			INFINITY
		};
	}
}

float2	SegmentSegmentIntersection(float2 a, float2 b, float2 c, float2 d) {
	float2 PointOfIntersect = LineLineIntersection(a, b, c, d);
	if (PointOfIntersect.x == INFINITY
		|| PointOfIntersect.y == INFINITY) {
		return (float2){INFINITY, INFINITY};
	}
	if (Vec2fLength((float2){b.x - a.x, b.y - a.y}) < Vec2fLength((float2){PointOfIntersect.x - a.x, PointOfIntersect.y - a.y})
		|| Vec2fLength((float2){d.x - c.x, d.y - c.y}) < Vec2fLength((float2){PointOfIntersect.x - c.x, PointOfIntersect.y - c.y})) {
		return (float2){
			INFINITY,
			INFINITY
		};
	} else {
		return PointOfIntersect;
	}
}

float2	LineSegmentIntersection(float2 a, float2 b, float2 c, float2 d) {
	float2 PointOfIntersect = LineLineIntersection(a, b, c, d);
	if (PointOfIntersect.x == INFINITY
		|| PointOfIntersect.y == INFINITY) {
		return (float2){INFINITY, INFINITY};
	}
	float2 example = (float2){d.x - c.x, d.y - c.y}, sample = (float2){PointOfIntersect.x - c.x, PointOfIntersect.y - c.y};
	if (dot(normalize(example), normalize(sample)) < 0.f
			|| Vec2fLength(example) < Vec2fLength(sample)) {
		return (float2){INFINITY, INFINITY};
	} else {
		return PointOfIntersect;
	}
}

float2	pInter;

float	Func(segment seg, float2 d, float2 p) {
	segment dir = (segment){
		p,
		(float2){p.x + d.x, p.y + d.y}
	};

	float2 PointOfIntersect = LineSegmentIntersection(dir.p0, dir.p1, seg.p0, seg.p1);

	float2 vec2fIntersection = (float2){PointOfIntersect.x - origin.x, PointOfIntersect.y - origin.y};
	if (dot(d, normalize(vec2fIntersection)) < 0.f) {
		return INFINITY;
	} else {
		pInter = PointOfIntersect;
		return Vec2fLength(vec2fIntersection);
	}
}

float	GetDist(float2 d, float2 p) {
	float distMin = INFINITY;
	int mapSize = sizeof(map) / sizeof(segment);

	for (int i = 0; i != mapSize; i += 1) {
		float temp = Func(map[i], d, p);
		if (temp < distMin) {
			activeSegment = map + i;
			distMin = temp;
		}
	}
	return distMin;
}

uint	GetTextureColor(float2 d, float dist, float h, float currH) {
	float ln = Vec2fLength((float2){
		activeSegment->p1.x - activeSegment->p0.x,
		activeSegment->p1.y - activeSegment->p0.y
	});

	float dx = ln / (float)txr->w;
	float dy = h / (float)txr->h;

	float2 p = (float2){
		origin.x + d.x * dist,
		origin.y + d.y * dist
	};
	float ln2 = Vec2fLength((float2){
		p.x - activeSegment->p0.x,
		p.y - activeSegment->p0.y
	});

	int x = ln2 / dx;
	int y = currH / dy;

	return img[x + txr->w * y];
}

void	DrawLine(int x, float origDist, float dist, float2 d) {
	float lineSize = clamp((H / dist) * distPlane, 0, H);
	int border = (H - (int)lineSize) / 2;
	for (int i = 0; i != (int)lineSize; i += 1) {
		if (1) {
			float temp = (H / dist) * distPlane;
			float offset = clamp((temp - H) / 2.f, 0, INFINITY);
			pxl[x + W * (border + i)] = GetTextureColor(d, origDist, temp, i + offset);
		} else {
			pxl[x + W * (border + i)] = 0x0000ff;
		}
	}
}

void	RenderWindow(float alpha) {
	float screenLen = tanf(alpha / 2.f) * distPlane;
	float segmentLen = screenLen / (W / 2.f);

	for (int i = -W / 2; i < W / 2; i += 1) {
		float a = atanf((segmentLen * i) / distPlane);
		float2 d = normalize(RotationVec2f(direct, angle + a));
		float temp = GetDist(d, origin);
		if (temp != INFINITY) {
			DrawLine(i + W / 2, temp, temp * cos(a) + (float)1e-4, d);
		}
	}
	return;
}

int		SDL_Prepare() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0 || IMG_Init(IMG_INIT_PNG) < 0) {
		return -1;
	}
	if (!(win = SDL_CreateWindow("Win", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN))) {
		return -1;
	}
	if (!(sfe = SDL_GetWindowSurface(win))) {
		return -1;
	}
	txr = IMG_Load("txr.png");
	txr = SDL_ConvertSurfaceFormat(txr, SDL_PIXELFORMAT_BGRA32, 0);
	img = txr->pixels;
	txr2 = IMG_Load("floor.png");
	txr2 = SDL_ConvertSurfaceFormat(txr2, SDL_PIXELFORMAT_BGRA32, 0);
	img2 = txr2->pixels;
	return 0;
}

void	MovePlayer(int f) {
	if (f) {
		float2 dir = RotationVec2f(direct, angle);
		if (GetDist(dir, origin) > step) {
			origin = (float2){
				origin.x + dir.x * step,
				origin.y + dir.y * step
			};
		}
	} else {
		float2 dir = RotationVec2f(direct, M_PI + angle);
		if (GetDist(dir, origin) > step) {
			origin = (float2){
				origin.x + dir.x * step,
				origin.y + dir.y * step
			};
		}
	}
}

void	FUNCTION(float alpha);

void	SDL_Loop() {
	SDL_Event evt;

	while (1) {
		SDL_PollEvent(&evt);
		if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN
										&& evt.key.keysym.sym == SDLK_ESCAPE))
			break ;
		if (evt.type == SDL_KEYDOWN && (evt.key.keysym.sym == SDLK_LEFT || evt.key.keysym.sym == SDLK_RIGHT)) {
			angle += (M_PI / 180.f) * (evt.key.keysym.sym == SDLK_LEFT ? -1.f : 1.f);
			direct = normalize(RotationVec2f((float2){1, 0}, angle));
			bzero(pxl, sizeof(uint32_t) * W * H);
			FUNCTION(fov);
			RenderWindow(fov);
			SDL_UpdateWindowSurface(win);
		}
		if (evt.type == SDL_KEYDOWN && (evt.key.keysym.sym == SDLK_UP || evt.key.keysym.sym == SDLK_DOWN)) {
			MovePlayer(evt.key.keysym.sym == SDLK_UP);
			bzero(pxl, sizeof(uint32_t) * W * H);
			FUNCTION(fov);
			RenderWindow(fov);
			SDL_UpdateWindowSurface(win);
		}
		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
	}
}

void	f1(int y, float origDist, float dist, float2 d) {
	float lineSize = clamp((W / dist) * distPlane, 0, W);
	int border = (W - (int)lineSize) / 2;
	for (int i = 0; i != (int)lineSize; i += 1) {
		pxl[(border + i) + W * y] = 0x303030;
	}
}

void	f0(float alpha) {
	float ldistPlane = 1.f;
	float screenLen = tanf(alpha / 2.f) * ldistPlane;
	float segmentLen = screenLen / (H / 2.f);

	array = malloc(sizeof(float2) * (H / 2 - 1));
	bzero(array, sizeof(float2) * (H / 2 - 1));
	aSize = H / 2 - 1;

	for (int i = 1; i != H / 2; i += 1) {
		float a = atanf((segmentLen * i) / ldistPlane);
		float2 d = normalize(RotationVec2f((float2){ldistPlane, 0}, -a));
		float2 p = LineLineIntersection(
			(float2){0, ldistPlane}, (float2){d.x, ldistPlane + d.y},
			(float2){0, 0}, (float2){1, 0}
		);

		array[i - 1] = p;
		float dist = Vec2fLength((float2){p.x - 0, p.y - ldistPlane});
	}
	return;
}

uint32_t	convert(float r, float g, float b) {
	r = clamp(r, 0.f, 255.f);
	g = clamp(g, 0.f, 255.f);
	b = clamp(b, 0.f, 255.f);

	uint32_t color = 0;
	color |= (uint32_t)r << 16;
	color |= (uint32_t)g << 8;
	color |= (uint32_t)b;
	return color;
}

void	FUNCTION(float alpha) {
	float screenLen = tanf(alpha / 2.f) * distPlane;
	float segmentLen = screenLen / (W / 2.f);

	for (int i = -W / 2; i < W / 2; i += 1) {
		float a = atanf((segmentLen * i) / distPlane);
		float2 d = normalize(RotationVec2f(direct, angle + a));
		float2 normalD = normalize(RotationVec2f(normalDirect, angle + a));

		float mapW = 50.f * 1;
		float mapH = 50.f * 1;
		float dx = mapW / txr2->w;
		float dy = mapH / txr2->h;

		for (int j = 0; j != (H / 2 - 1); j += 1) {
			float coeff = (Vec2fLength(array[j]) / cosf(a)) / Vec2fLength(array[j]);

			float2 correctPoint = (float2){
				array[j].x * coeff,
				array[j].y * coeff
			};

			float2 point = (float2){
				d.x * (correctPoint.x) + normalD.x * (correctPoint.y),
				d.y * (correctPoint.x) + normalD.y * (correctPoint.y)
			};
			{
				point.x += origin.x;
				point.y += origin.y;
			}
			float x = point.x + mapW / 2.f;
			float y = point.y + mapH / 2.f;
			if (x >= 0 && x < mapW && y >= 0 && y < mapH) {
				pxl[(i + W / 2) + W * (j + H / 2)] = img2[(int)(x / dx) + txr2->w * (int)(y / dy)];
				pxl[(i + W / 2) + W * (H / 2 - j)] = img2[(int)(x / dx) + txr2->w * (int)(y / dy)];
			} else {
				pxl[(i + W / 2) + W * (j + H / 2)] = 0x0;
			}
		}
	}
	return;
}

int	main() {
	if (SDL_Prepare())
		exit(0);
	pxl = sfe->pixels;
	direct = normalize(RotationVec2f((float2){1, 0}, angle));
	f0(fov);
	FUNCTION(fov);
	RenderWindow(fov);
	SDL_UpdateWindowSurface(win);
	SDL_Loop();
	exit(0);
}
