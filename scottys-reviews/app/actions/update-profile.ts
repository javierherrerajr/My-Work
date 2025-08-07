'use server';

import { prisma } from "@/lib/prisma";
import { redirect } from "next/navigation";

export async function updateProfile(formData: FormData) {
  const userId = formData.get('userId') as string;
  const username = formData.get('username') as string;
  const major = formData.get('major') as string;
  const expectedGradYear = formData.get('expectedGradYear');
  const aboutMe = formData.get('aboutMe') as string;
  const status = formData.get('status') as string;

  await prisma.user.update({
    where: { id: userId },
    data: {
      username: username || null,
      major: major || null,
      expectedGradYear: expectedGradYear ? parseInt(expectedGradYear as string) : null,
      aboutMe: aboutMe || null,
      status: status || null,
    },
  });

  redirect("/profile");
}
