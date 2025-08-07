import { NextResponse } from "next/server";
import { prisma } from "@/lib/prisma";

export async function GET(request: Request) {
  const { searchParams } = new URL(request.url);
  const query = searchParams.get("q") || "";
  const department = searchParams.get("department") || "";
  const subject = searchParams.get("subject") || "";

  try {
    const courses = await prisma.class.findMany({
      where: {
        AND: [
          {
            OR: [
              { classname: { contains: query, mode: "insensitive" } },
              { courseid: { contains: query, mode: "insensitive" } },
            ],
          },
        ],
      },
      orderBy: { courseid: "asc" },
    });

    return NextResponse.json(courses);
  } catch (error) {
    console.error("Error searching courses:", error);
    return NextResponse.json(
      { error: "Failed to search courses" },
      { status: 500 }
    );
  }
}