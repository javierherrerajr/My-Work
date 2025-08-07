import { getServerSession } from "next-auth";
import { authConfig } from "@/auth.config";
import { prisma } from "@/lib/prisma";
import { NextResponse } from "next/server";

export async function GET() {
  try {
    const session = await getServerSession(authConfig);
    console.log("API: Session data:", session);

    if (!session?.user?.id && !session?.user?.netid) {
      console.log("API: No user ID or NetID in session");
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

    console.log("API: Found user:", user);

    if (!user) {
      console.log("API: User not found");
      return new NextResponse(JSON.stringify({ error: "User not found" }), {
        status: 404,
      });
    }

    return NextResponse.json(user);
  } catch (error) {
    console.error("API: Error in profile route:", error);
    return new NextResponse(JSON.stringify({ error: "Internal server error" }), {
      status: 500,
    });
  }
} 