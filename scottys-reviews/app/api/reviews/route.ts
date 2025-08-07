import { prisma } from "@/lib/prisma";
import { NextResponse } from "next/server";
import { getServerSession } from "next-auth";
import { authConfig } from "@/auth.config";
import { z } from "zod";

const schema = z.object({
  courseid: z.string(),
  rating: z.number().min(1).max(10),
  quarter: z.string(),
  professor: z.string().optional(),
  ta: z.string().optional(),
  review: z.string(),
});

export async function GET() {
  try {
    const reviews = await prisma.review.findMany({
      orderBy: { reviewid: "desc" },
      include: {
        user: {
          select: {
            id: true,
            username: true,
          },
        },
        course: true,
      },
    });

    return NextResponse.json(reviews);
  } catch (err) {
    return NextResponse.json({ error: "Failed to fetch reviews." }, { status: 500 });
  }
}

export async function POST(req: Request) {
  const session = await getServerSession(authConfig);
  if (!session?.user || !session.user.netid) {
    return NextResponse.json({ error: "Unauthorized" }, { status: 401 });
  }

  const body = await req.json();
  const result = schema.safeParse(body);

  if (!result.success) {
    return NextResponse.json({ error: "Invalid input", details: result.error.format() }, { status: 400 });
  }

  const { courseid, rating, quarter, professor, ta, review } = result.data;

  try {
    const createdReview = await prisma.review.create({
      data: {
        courseid,
        userId: session.user.id, // not netid
        rating,
        quarter,
        professor: professor || "NA",
        ta: ta || "NA",
        review,
      },
    });

    return NextResponse.json({ success: true, review: createdReview });
  } catch (error) {
    return NextResponse.json({ error: "Failed to submit review." }, { status: 500 });
  }
}