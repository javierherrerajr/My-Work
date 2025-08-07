import { getServerSession } from "next-auth";
import { authConfig } from "@/auth.config";
import { prisma } from "@/lib/prisma";
import { NextResponse } from "next/server";

export async function GET() {
  const session = await getServerSession(authConfig);

  if (!session?.user?.id && !session?.user?.netid) {
    return new NextResponse(JSON.stringify({ error: "Unauthorized" }), {
      status: 401,
    });
  }

  const user = await prisma.user.findFirst({
    where: {
      OR: [
        { id: session.user?.id },
        { netid: session.user?.netid },
      ],
    },
  });

  if (!user) {
    return new NextResponse(JSON.stringify({ error: "User not found" }), {
      status: 404,
    });
  }

  try {
    const reviews = await prisma.review.findMany({
      where: { userId: user.id },
      include: {
        course: {
          select: {
            courseid: true,
            classname: true,
          },
        },
      },
      orderBy: { reviewid: 'desc' },
    });

    console.log('Found reviews:', reviews); // 添加调试日志
    return NextResponse.json(reviews);
  } catch (error) {
    console.error('Error fetching reviews:', error);
    return new NextResponse(JSON.stringify({ error: "Failed to fetch reviews" }), {
      status: 500,
    });
  }
} 