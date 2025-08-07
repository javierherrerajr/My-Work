// app/api/auth/forgot/route.ts
import { prisma } from "@/lib/prisma";
import { randomBytes } from "crypto";
import { NextResponse } from "next/server";

export async function POST(req: Request) {
  const { netid } = await req.json();

  const user = await prisma.user.findUnique({ where: { netid } });
  if (!user) {
    return NextResponse.json({ message: "If an account exists, a reset link has been generated." });
  }

  const token = randomBytes(32).toString("hex");
  const expiry = new Date(Date.now() + 30 * 60 * 1000); // 30 min

  await prisma.user.update({
    where: { netid },
    data: {
      resetToken: token,
      resetTokenExpiry: expiry,
    },
  });

  // 🔧 Replace with your dev URL
  const resetUrl = `http://localhost:3000/reset-password?token=${token}`;

  return NextResponse.json({
    message: "Reset link generated.",
    resetUrl, // ✅ Display this link in the frontend or console for local use
    token     // optional: can omit in production
  });
}